//
// RiskJS.cpp
// ~~~~~~~~~~~
//
//

#include <string>
#include <sstream>

#include <node.h>

#include "CVaR.h"


namespace RiskJS {


void JS_CVaRHistorical(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::Isolate* isolate = info.GetIsolate();

    // Check the number and type of arguments passed
    if (info.Length() != 3 || !info[0]->IsArray() || !info[1]->IsArray() || !info[2]->IsNumber()) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(v8::Exception::TypeError(
            v8::String::NewFromUtf8(isolate,
                "needs three arguments",
                v8::NewStringType::kNormal).ToLocalChecked()));
        return;
    }

    // Compute parameters and call function
    std::string cvarOut;
    try {
        priceData rawPrices;
        weightData weights;
        double alphatest;

        v8::Local<v8::Array> jsArr;

        // Process rawPrices
        jsArr = v8::Local<v8::Array>::Cast(info[0]);
        for (int r = 0; r < jsArr->Length(); r++) {
            priceRow row;
            v8::Local<v8::Array> jsRow = v8::Local<v8::Array>::Cast(jsArr->Get(r));
            for (int c = 0; c < jsRow->Length(); c++) {
                std::string elem(*v8::String::Utf8Value(isolate, jsRow->Get(c)));
                row.push_back(elem);
            }
            rawPrices.push_back(row);
        }

        // Process weights
        jsArr = v8::Local<v8::Array>::Cast(info[1]);
        for (int i = 0; i < jsArr->Length(); i++) {
            double elem(jsArr->Get(i)->NumberValue());
            weights.push_back(elem);
        }

        // Process alphatest
        alphatest = info[2]->NumberValue();

        // Call our function
        cvarOut = std::to_string(CVaRHistorical(rawPrices, weights, alphatest));
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
    info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, cvarOut.c_str(), v8::NewStringType::kNormal).ToLocalChecked());
}

void JS_CVaRMonteCarlo(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::Isolate* isolate = info.GetIsolate();

    // Check the number and type of arguments passed
    if (info.Length() != 3 || !info[0]->IsArray() || !info[1]->IsArray() || !info[2]->IsNumber()) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(v8::Exception::TypeError(
            v8::String::NewFromUtf8(isolate,
                "needs three arguments",
                v8::NewStringType::kNormal).ToLocalChecked()));
        return;
    }

    // Compute parameters and call function
    std::string cvarOut;
    try {
        priceData rawPrices;
        weightData weights;
        double alphatest;

        v8::Local<v8::Array> jsArr;

        // Process rawPrices
        jsArr = v8::Local<v8::Array>::Cast(info[0]);
        for (int r = 0; r < jsArr->Length(); r++) {
            priceRow row;
            v8::Local<v8::Array> jsRow = v8::Local<v8::Array>::Cast(jsArr->Get(r));
            for (int c = 0; c < jsRow->Length(); c++) {
                std::string elem(*v8::String::Utf8Value(isolate, jsRow->Get(c)));
                row.push_back(elem);
            }
            rawPrices.push_back(row);
        }

        // Process weights
        jsArr = v8::Local<v8::Array>::Cast(info[1]);
        for (int i = 0; i < jsArr->Length(); i++) {
            double elem(jsArr->Get(i)->NumberValue());
            weights.push_back(elem);
        }

        // Process alphatest
        alphatest = info[2]->NumberValue();

        // Call our function
        cvarOut = std::to_string(CVaRMonteCarlo(rawPrices, weights, alphatest));
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
    info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, cvarOut.c_str(), v8::NewStringType::kNormal).ToLocalChecked());
}

void JS_CVaRVarianceCovariance(const v8::FunctionCallbackInfo<v8::Value>& info) {
    v8::Isolate* isolate = info.GetIsolate();

    // Check the number and type of arguments passed
    if (info.Length() != 3 || !info[0]->IsArray() || !info[1]->IsArray() || !info[2]->IsNumber()) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(v8::Exception::TypeError(
            v8::String::NewFromUtf8(isolate,
                "needs three arguments",
                v8::NewStringType::kNormal).ToLocalChecked()));
        return;
    }

    // Compute parameters and call function
    std::string cvarOut;
    try {
        priceData rawPrices;
        weightData weights;
        double alphatest;

        v8::Local<v8::Array> jsArr;

        // Process rawPrices
        jsArr = v8::Local<v8::Array>::Cast(info[0]);
        for (int r = 0; r < jsArr->Length(); r++) {
            priceRow row;
            v8::Local<v8::Array> jsRow = v8::Local<v8::Array>::Cast(jsArr->Get(r));
            for (int c = 0; c < jsRow->Length(); c++) {
                std::string elem(*v8::String::Utf8Value(isolate, jsRow->Get(c)));
                row.push_back(elem);
            }
            rawPrices.push_back(row);
        }

        // Process weights
        jsArr = v8::Local<v8::Array>::Cast(info[1]);
        for (int i = 0; i < jsArr->Length(); i++) {
            double elem(jsArr->Get(i)->NumberValue());
            weights.push_back(elem);
        }

        // Process alphatest
        alphatest = info[2]->NumberValue();

        // Call our function
        cvarOut = std::to_string(CVaRVarianceCovariance(rawPrices, weights, alphatest));
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
    info.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, cvarOut.c_str(), v8::NewStringType::kNormal).ToLocalChecked());
}

void Init(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "CVaRHistorical", JS_CVaRHistorical);
    NODE_SET_METHOD(exports, "CVaRMonteCarlo", JS_CVaRMonteCarlo);
    NODE_SET_METHOD(exports, "CVaRVarianceCovariance", JS_CVaRVarianceCovariance);
}

}  // namespace RiskJS

NODE_MODULE(NODE_GYP_MODULE_NAME, RiskJS::Init)
