//
// RiskJS.cpp
// ~~~~~~~~~~~
//
//

#include <string>

#include <node.h>

#include "ptf_mc_var.h"

namespace RiskJS {

using namespace v8;
using namespace std;


void JS_portfolioMonteCarloVaR(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number and type of arguments passed
    if (args.Length() != 1 || args[0]->IsArray()) {
        // Throw an Error that is passed back to JavaScript
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate,
                                "Needs one argument with the data array",
                                NewStringType::kNormal).ToLocalChecked()));
        return;
    }

    // TODO: compute data array
    dataArray data;

    // Call our function
    auto varOut = portfolioMonteCarloVaR(data);

    // Return our result
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, to_string(varOut).c_str(), NewStringType::kNormal).ToLocalChecked());
}

void Init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "portfolioMonteCarloVaR", JS_portfolioMonteCarloVaR);
}

}  // namespace RiskJS

NODE_MODULE(NODE_GYP_MODULE_NAME, RiskJS::Init)
