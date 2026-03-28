#pragma once


namespace Nonsense
{
    
class UObject
{
public:
    UObject();
    virtual ~UObject();

    virtual void Destroy();
    bool IsPendingDestroy() const { return mIsPedingDestroy; }

private:
    bool mIsPedingDestroy;

};

} // namespace Nonsense