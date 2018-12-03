#pragma once

class CShape
{
public:
	CShape();
	CShape(CPoint startPos);

	virtual ~CShape();

public:
	CPoint Start;
	CPoint End;
};