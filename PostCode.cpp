#include "PostCode.h"

PostCode::PostCode(int code)
{
	this->code = code;
	//можно хранить other
}
PostCode::~PostCode()
{

}

int PostCode::GetCode()
{
	return code;
}
