#include "PostCode.h"

PostCode::PostCode(int code)
{
	this->code = code;
	//����� ������� other
}
PostCode::~PostCode()
{

}

int PostCode::GetCode()
{
	return code;
}
