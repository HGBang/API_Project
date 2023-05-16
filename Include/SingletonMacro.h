#pragma once

#define DECLARE_SINGLE(Type) \
private:\
static Type*	m_Inst; \
public:\
static	Type* GetInst()\
{\
if(!m_Inst)\
m_Inst = new Type;\
return m_Inst;\
}\
static void DestoyInst()\
{\
if(m_Inst)\
{\
delete m_Inst;\
m_Inst = nullptr;\
}\
}\
private:\
Type();\
~Type();

#define DEFINITION_SINGLE(Type) Type* Type::m_Inst = nullptr;