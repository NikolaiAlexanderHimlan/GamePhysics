//Various little things which make coding easier/clearer
#define REF(DataType) const DataType&
#define OUT_PARAM(DataType) DataType* /*Makes it clear that this parameter is used as an output.*/
#define OUT_SET(outParam, value) if(outParam != nullptr){ *outParam = value; }

//TODO: Need to figure out how to have the value on the left, so it can be used as a get.  Just returning the pointer for now, no check.
#define SAFE_GET(pointerVal, defaultVal) \
pointerVal
/*(pointerVal == nullptr) ? pointerVal = defaultVal : pointerVal*/
#define SAFE_ASSIGN(pointerVar) if(pointerVar != nullptr) { delete pointerVar; } pointerVar /*= [new value]*/
#define SAFE_DELETE(pointerVar) if(pointerVar != nullptr) { delete pointerVar; pointerVar = nullptr; }

#define BoolToStr(boolIn) (boolIn?"True":"False")
#define EnableToStr(boolIn) (boolIn?"Enabled":"Disabled")
