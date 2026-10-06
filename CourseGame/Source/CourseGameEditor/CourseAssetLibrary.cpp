#include "CourseAssetLibrary.h"
#include "Gameplay/CourseBeacon.h"
#include "Engine/Blueprint.h"
#include "EdGraph/EdGraph.h"
#include "EdGraphSchema_K2.h"
#include "K2Node_Event.h"
#include "K2Node_CallFunction.h"
#include "K2Node_FormatText.h"
#include "K2Node_Self.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
bool UCourseAssetLibrary::AddBeaconPresentation(UBlueprint* Blueprint)
{
    if (!Blueprint || !Blueprint->ParentClass->IsChildOf(ACourseBeacon::StaticClass())) return false;
    UEdGraph* Graph = FBlueprintEditorUtils::FindEventGraph(Blueprint);
    if (!Graph) return false;
    const UEdGraphSchema_K2* Schema = GetDefault<UEdGraphSchema_K2>();
    auto Place = [Graph](UEdGraphNode* Node, int32 X, int32 Y) {
        Graph->AddNode(Node, false, false); Node->CreateNewGuid();
        Node->NodePosX = X; Node->NodePosY = Y; Node->AllocateDefaultPins();
    };
    UK2Node_Event* Event = NewObject<UK2Node_Event>(Graph);
    Event->EventReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(ACourseBeacon, OnChargeChanged), ACourseBeacon::StaticClass());
    Event->bOverrideFunction = true;
    Place(Event, 0, 0);
    UK2Node_Self* Self = NewObject<UK2Node_Self>(Graph); Place(Self, 0, 220);
    auto Call = [&](UClass* Owner, FName Name, int32 X, int32 Y) {
        UK2Node_CallFunction* Node = NewObject<UK2Node_CallFunction>(Graph);
        Node->SetFromFunction(Owner->FindFunctionByName(Name)); Place(Node, X, Y); return Node;
    };
    UK2Node_CallFunction* DisplayName = Call(UKismetSystemLibrary::StaticClass(), TEXT("GetDisplayName"), 220, 220);
    UK2Node_FormatText* Format = NewObject<UK2Node_FormatText>(Graph); Place(Format, 480, 160);
    Schema->TrySetDefaultText(*Format->GetFormatPin(), FText::FromString(TEXT("{Name}: charge {Charge}")));
    UK2Node_CallFunction* Convert = Call(UKismetTextLibrary::StaticClass(), TEXT("Conv_TextToString"), 770, 160);
    UK2Node_CallFunction* Print = Call(UKismetSystemLibrary::StaticClass(), TEXT("PrintString"), 1030, 0);
    auto Connect = [Schema](UEdGraphPin* From, UEdGraphPin* To) { return From && To && Schema->TryCreateConnection(From, To); };
    bool bOK = Connect(Event->FindPin(UEdGraphSchema_K2::PN_Then), Print->FindPin(UEdGraphSchema_K2::PN_Execute));
    bOK &= Connect(Self->FindPin(UEdGraphSchema_K2::PN_Self), DisplayName->FindPin(TEXT("Object")));
    bOK &= Connect(DisplayName->FindPin(UEdGraphSchema_K2::PN_ReturnValue), Format->FindArgumentPin(TEXT("Name")));
    bOK &= Connect(Event->FindPin(TEXT("NewCharge")), Format->FindArgumentPin(TEXT("Charge")));
    bOK &= Connect(Format->FindPin(TEXT("Result")), Convert->FindPin(TEXT("InText")));
    bOK &= Connect(Convert->FindPin(UEdGraphSchema_K2::PN_ReturnValue), Print->FindPin(TEXT("InString")));
    FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);
    FKismetEditorUtilities::CompileBlueprint(Blueprint);
    return bOK && Blueprint->Status != BS_Error;
}
bool UCourseAssetLibrary::CanActorEverTick(AActor* Actor) { return Actor && Actor->PrimaryActorTick.bCanEverTick; }
