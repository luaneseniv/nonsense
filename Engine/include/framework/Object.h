#pragma once


namespace Nonsense
{
    
class UObject
{
public:
    UObject();
    virtual ~UObject();

    void Destroy();
    bool IsPendingDestroy() const { return mIsPedingDestroy; }
private:
    bool mIsPedingDestroy;

};

} // namespace Nonsense