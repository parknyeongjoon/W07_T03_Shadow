#include "RotatingMovementComponent.h"

#include "Components/PrimitiveComponents/PrimitiveComponent.h"
#include "UObject/Casts.h"
#include "UObject/ObjectFactory.h"

URotatingMovementComponent::URotatingMovementComponent()
{
}

URotatingMovementComponent::URotatingMovementComponent(const URotatingMovementComponent& other)
    : RotationRate(other.RotationRate)
{
    
}

void URotatingMovementComponent::TickComponent(float DeltaTime)
{
    const FRotator OldRotation = UpdatedComponent->GetComponentRotation();
    const FRotator DeltaRotation = (RotationRate * DeltaTime / 1000.0f);
    FRotator NewRotation = OldRotation.Add(DeltaRotation.Pitch, DeltaRotation.Yaw, DeltaRotation.Roll);

    UpdatedComponent->SetRelativeRotation(NewRotation);
}

UObject* URotatingMovementComponent::Duplicate() const
{
    URotatingMovementComponent* NewComp = FObjectFactory::ConstructObjectFrom<URotatingMovementComponent>(this);
    NewComp->DuplicateSubObjects(this);
    NewComp->PostDuplicate();
    return NewComp;
}

void URotatingMovementComponent::DuplicateSubObjects(const UObject* Source)
{
    UMovementComponent::DuplicateSubObjects(Source);

    URotatingMovementComponent* SourceComp = Cast<URotatingMovementComponent>(Source);
    if (SourceComp)
    {
        RotationRate = SourceComp->RotationRate;
    }
}

void URotatingMovementComponent::PostDuplicate()
{
    UMovementComponent::PostDuplicate();
}

std::shared_ptr<FActorComponentInfo> URotatingMovementComponent::GetActorComponentInfo()
{
    std::shared_ptr<FRotatingMovementComponentInfo> Info = std::make_shared<FRotatingMovementComponentInfo>();
    Super::GetActorComponentInfo()->Copy(*Info);
    Info->RotationRate = RotationRate;
    return Info;
}

void URotatingMovementComponent::LoadAndConstruct(const FActorComponentInfo& Info)
{
    Super::LoadAndConstruct(Info);
    const FRotatingMovementComponentInfo& RotatingMovementInfo = static_cast<const FRotatingMovementComponentInfo&>(Info);
    RotationRate = RotatingMovementInfo.RotationRate;
}
