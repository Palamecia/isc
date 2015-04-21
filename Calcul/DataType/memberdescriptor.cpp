#include "memberdescriptor.h"

MemberDescriptor::MemberDescriptor(const String &name) :
    m_name(name)
{}

String& MemberDescriptor::name() {
    return m_name;
}

const String& MemberDescriptor::name() const {
    return m_name;
}
