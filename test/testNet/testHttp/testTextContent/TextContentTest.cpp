
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TextContent.hpp"
#include "Reflect.hpp"
#include "Field.hpp"
#include "ArrayList.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(TextMember) {
public:
    int value;
    DECLARE_REFLECT_FIELD(TextMember,value)    
};

DECLARE_SIMPLE_CLASS(TextData) {
public:
    String name;
    String member;
    TextMember member2;
    ArrayList<TextMember> lists;

    DECLARE_REFLECT_FIELD(TextData,name,member,member2,lists)
};

int main() {
    TextData data1 = createTextData();
    data1->member2 = createTextMember();
    data1->member2->value = 100;

    data1->lists = createArrayList<TextMember>();
    TextMember member = createTextMember();
    member->value = 1;

    TextMember member2 = createTextMember();
    member2->value = 2;
    
    data1->lists->add(member);
    data1->lists->add(member2);

    data1->name = createString("nameTag");
    data1->member = createString("memberTag");

    TextContent content = createTextContent(data1);
    printf("data is %s \n",content->get()->toChars());

}
