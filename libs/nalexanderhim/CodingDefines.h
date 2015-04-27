//Various little things which make coding easier/clearer
#define REF(DataType) const DataType&
#define OUT_PARAM(DataType) DataType* /*Makes it clear that this parameter is used as an output.*/
#define OUT_SET(outParam, value) if(outParam != nullptr){ *outParam = value; }

#define BoolToStr(boolIn) (boolIn?"True":"False")
#define EnableToStr(boolIn) (boolIn?"Enabled":"Disabled")
