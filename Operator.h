#pragma once
#include <iostream>
class Operator
{
    int num;

public:
    //+記号をオーバーロード
    Operator operator +(Operator r)
    {
        Operator tc;
        tc.num = this->num + r.num;
        return tc;
    }
    //-記号をオーバーロード
    Operator operator -(Operator &r)const
    {
        Operator tc;
        tc.num = this->num - r.num;
        return tc;
    }
    //*記号をオーバーロード
    Operator operator *(Operator &r)const
    {
        Operator tc;
        tc.num = this->num * r.num;
        return tc;
    }
    // /記号をオーバーロード
    Operator operator /(Operator &r)const
    {
        Operator tc;
        tc.num = this->num / r.num;
        return tc;
    }
    //代入演算子のオーバーロード
    Operator& operator =(const Operator& r)
    {
        num = r.num;
        return *this;
    }

    Operator(int x = 0) { num = x; }
    int get() { return num; }
    void set(int x) { num = x; }
};


