#include "stdafx.h"
#include "Observerable.h"


Observerable::Observerable():_bChange(false)
{

}


Observerable::~Observerable()
{
}


// 注册观察者
void Observerable::Attach(Observer* pOb)
{
    if (pOb == NULL)
    {
        return;
    }

    // 看看当前列表中是否有这个观察者
    auto it = _Obs.begin();
    for (; it != _Obs.end(); it++)
    {
        if (*it == pOb)
        {
            return;
        }
    }

    _Obs.push_back(pOb);
}

// 反注册观察者
void Observerable::Detach(Observer* pOb)
{
    if ((pOb == NULL) || (_Obs.empty() == true))
    {
        return;
    }

    _Obs.remove(pOb);
}

void Observerable::SetChange(string news)
{
    _bChange = true;

    Notify( ( (void*)news.c_str() ));
}


void Observerable::Notify(void* pArg)
{
    if (_bChange == false)
    {
        return;
    }

    // 看看当前列表中是否有这个观察者
    auto it = _Obs.begin();
    for (; it != _Obs.end(); it++)
    {
        (*it)->Update(pArg);
    }

    _bChange = false;
}
