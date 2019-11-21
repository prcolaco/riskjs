//
// RiskJS.cpp
// ~~~~~~~~~~~
//
//

#include <string>
#include <sstream>

#include <node.h>

#include "ptf_mc_var.h"


namespace RiskJS {


void JS_portfolioMonteCarloVaR(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::Isolate* isolate = info.GetIsolate();

    // Check the number and type of arguments passed
    if (info.Length() != 1 || !info[0]->IsArray()) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(v8::Exception::TypeError(
            v8::String::NewFromUtf8(isolate,
                "needs one argument with the price data array",
                v8::NewStringType::kNormal).ToLocalChecked()));
        return;
    }

    // Compute price data array and call monte carlo var
    std::string varOut;
    try {
        priceData data;
        v8::Local<v8::Array> jsArr = v8::Local<v8::Array>::Cast(info[0]);
        for (int r = 0; r < jsArr->Length(); r++) {
            priceRow row;
            v8::Local<v8::Array> jsRow = v8::Local<v8::Array>::Cast(jsArr->Get(r));
            for (int c = 0; c < jsRow->Length(); c++) {
                std::string elem(*v8::String::Utf8Value(isolate, jsRow->Get(c)));
                row.push_back(elem);
            }
            data.push_back(row);
        }

        // Call our function
        varOut = std::to_string(portfolioMonteCarloVaR(data));
    } catch (const std::exception& e) {
        // Throw an Error that is passed back to JavaScript
        std::stringstream msg;
        msg << "failed to process price data, reason '" << e.what() << "'";
        isolate->ThrowException(v8::Exception::TypeError(
            v8::String::NewFromUtf8(isolate, msg.str().c_str(),
                v8::NewStringType::kNormal).ToLocalChecked()));
        return;
    }

    // Return our result
    info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, varOut.c_str(), v8::NewStringType::kNormal).ToLocalChecked());
}

void Init(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "portfolioMonteCarloVaR", JS_portfolioMonteCarloVaR);
}

}  // namespace RiskJS

NODE_MODULE(NODE_GYP_MODULE_NAME, RiskJS::Init)
