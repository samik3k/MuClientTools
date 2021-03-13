#ifndef OZT_H
#define OZT_H

typedef ImgConvertor<EXT_OZT, 4> OztConvertor;
class OZT : public OztConvertor
{
public:
	OZT() {};
	virtual ~OZT() {};
};

#endif // !OZT_H
