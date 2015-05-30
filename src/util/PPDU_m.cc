//
// Generated file, do not edit! Created by nedtool 4.6 from util/PPDU.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "PPDU_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(pdDataInd);

pdDataInd::pdDataInd(const char *name, int kind) : ::cPacket(name,kind)
{
    this->psduLength_var = 0;
    this->ppduLinkQuality_var = 0;
}

pdDataInd::pdDataInd(const pdDataInd& other) : ::cPacket(other)
{
    copy(other);
}

pdDataInd::~pdDataInd()
{
}

pdDataInd& pdDataInd::operator=(const pdDataInd& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void pdDataInd::copy(const pdDataInd& other)
{
    this->psduLength_var = other.psduLength_var;
    this->ppduLinkQuality_var = other.ppduLinkQuality_var;
}

void pdDataInd::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->psduLength_var);
    doPacking(b,this->ppduLinkQuality_var);
}

void pdDataInd::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->psduLength_var);
    doUnpacking(b,this->ppduLinkQuality_var);
}

unsigned char pdDataInd::getPsduLength() const
{
    return psduLength_var;
}

void pdDataInd::setPsduLength(unsigned char psduLength)
{
    this->psduLength_var = psduLength;
}

unsigned char pdDataInd::getPpduLinkQuality() const
{
    return ppduLinkQuality_var;
}

void pdDataInd::setPpduLinkQuality(unsigned char ppduLinkQuality)
{
    this->ppduLinkQuality_var = ppduLinkQuality;
}

class pdDataIndDescriptor : public cClassDescriptor
{
  public:
    pdDataIndDescriptor();
    virtual ~pdDataIndDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(pdDataIndDescriptor);

pdDataIndDescriptor::pdDataIndDescriptor() : cClassDescriptor("pdDataInd", "cPacket")
{
}

pdDataIndDescriptor::~pdDataIndDescriptor()
{
}

bool pdDataIndDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<pdDataInd *>(obj)!=NULL;
}

const char *pdDataIndDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int pdDataIndDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int pdDataIndDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *pdDataIndDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "psduLength",
        "ppduLinkQuality",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int pdDataIndDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "psduLength")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "ppduLinkQuality")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *pdDataIndDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "unsigned char",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *pdDataIndDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int pdDataIndDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    pdDataInd *pp = (pdDataInd *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string pdDataIndDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    pdDataInd *pp = (pdDataInd *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getPsduLength());
        case 1: return ulong2string(pp->getPpduLinkQuality());
        default: return "";
    }
}

bool pdDataIndDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    pdDataInd *pp = (pdDataInd *)object; (void)pp;
    switch (field) {
        case 0: pp->setPsduLength(string2ulong(value)); return true;
        case 1: pp->setPpduLinkQuality(string2ulong(value)); return true;
        default: return false;
    }
}

const char *pdDataIndDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *pdDataIndDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    pdDataInd *pp = (pdDataInd *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(ppdu);

ppdu::ppdu(const char *name, int kind) : ::cPacket(name,kind)
{
    for (unsigned int i=0; i<4; i++)
        this->Preamble_var[i] = 0;
    this->SFD_var = 0;
    this->PHR_var = 0;
}

ppdu::ppdu(const ppdu& other) : ::cPacket(other)
{
    copy(other);
}

ppdu::~ppdu()
{
}

ppdu& ppdu::operator=(const ppdu& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void ppdu::copy(const ppdu& other)
{
    for (unsigned int i=0; i<4; i++)
        this->Preamble_var[i] = other.Preamble_var[i];
    this->SFD_var = other.SFD_var;
    this->PHR_var = other.PHR_var;
}

void ppdu::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->Preamble_var,4);
    doPacking(b,this->SFD_var);
    doPacking(b,this->PHR_var);
}

void ppdu::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->Preamble_var,4);
    doUnpacking(b,this->SFD_var);
    doUnpacking(b,this->PHR_var);
}

unsigned int ppdu::getPreambleArraySize() const
{
    return 4;
}

unsigned char ppdu::getPreamble(unsigned int k) const
{
    if (k>=4) throw cRuntimeError("Array of size 4 indexed by %lu", (unsigned long)k);
    return Preamble_var[k];
}

void ppdu::setPreamble(unsigned int k, unsigned char Preamble)
{
    if (k>=4) throw cRuntimeError("Array of size 4 indexed by %lu", (unsigned long)k);
    this->Preamble_var[k] = Preamble;
}

unsigned char ppdu::getSFD() const
{
    return SFD_var;
}

void ppdu::setSFD(unsigned char SFD)
{
    this->SFD_var = SFD;
}

unsigned char ppdu::getPHR() const
{
    return PHR_var;
}

void ppdu::setPHR(unsigned char PHR)
{
    this->PHR_var = PHR;
}

class ppduDescriptor : public cClassDescriptor
{
  public:
    ppduDescriptor();
    virtual ~ppduDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(ppduDescriptor);

ppduDescriptor::ppduDescriptor() : cClassDescriptor("ppdu", "cPacket")
{
}

ppduDescriptor::~ppduDescriptor()
{
}

bool ppduDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ppdu *>(obj)!=NULL;
}

const char *ppduDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ppduDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int ppduDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *ppduDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "Preamble",
        "SFD",
        "PHR",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int ppduDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='P' && strcmp(fieldName, "Preamble")==0) return base+0;
    if (fieldName[0]=='S' && strcmp(fieldName, "SFD")==0) return base+1;
    if (fieldName[0]=='P' && strcmp(fieldName, "PHR")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ppduDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "unsigned char",
        "unsigned char",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *ppduDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int ppduDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ppdu *pp = (ppdu *)object; (void)pp;
    switch (field) {
        case 0: return 4;
        default: return 0;
    }
}

std::string ppduDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ppdu *pp = (ppdu *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getPreamble(i));
        case 1: return ulong2string(pp->getSFD());
        case 2: return ulong2string(pp->getPHR());
        default: return "";
    }
}

bool ppduDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ppdu *pp = (ppdu *)object; (void)pp;
    switch (field) {
        case 0: pp->setPreamble(i,string2ulong(value)); return true;
        case 1: pp->setSFD(string2ulong(value)); return true;
        case 2: pp->setPHR(string2ulong(value)); return true;
        default: return false;
    }
}

const char *ppduDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *ppduDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ppdu *pp = (ppdu *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(edConf);

edConf::edConf(const char *name, int kind) : ::cMessage(name,kind)
{
    this->status_var = 0;
    this->EnergyLevel_var = 0;
}

edConf::edConf(const edConf& other) : ::cMessage(other)
{
    copy(other);
}

edConf::~edConf()
{
}

edConf& edConf::operator=(const edConf& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void edConf::copy(const edConf& other)
{
    this->status_var = other.status_var;
    this->EnergyLevel_var = other.EnergyLevel_var;
}

void edConf::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->status_var);
    doPacking(b,this->EnergyLevel_var);
}

void edConf::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->status_var);
    doUnpacking(b,this->EnergyLevel_var);
}

unsigned char edConf::getStatus() const
{
    return status_var;
}

void edConf::setStatus(unsigned char status)
{
    this->status_var = status;
}

unsigned char edConf::getEnergyLevel() const
{
    return EnergyLevel_var;
}

void edConf::setEnergyLevel(unsigned char EnergyLevel)
{
    this->EnergyLevel_var = EnergyLevel;
}

class edConfDescriptor : public cClassDescriptor
{
  public:
    edConfDescriptor();
    virtual ~edConfDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(edConfDescriptor);

edConfDescriptor::edConfDescriptor() : cClassDescriptor("edConf", "cMessage")
{
}

edConfDescriptor::~edConfDescriptor()
{
}

bool edConfDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<edConf *>(obj)!=NULL;
}

const char *edConfDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int edConfDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int edConfDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *edConfDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "status",
        "EnergyLevel",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int edConfDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+0;
    if (fieldName[0]=='E' && strcmp(fieldName, "EnergyLevel")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *edConfDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "unsigned char",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *edConfDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "phyState";
            return NULL;
        default: return NULL;
    }
}

int edConfDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    edConf *pp = (edConf *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string edConfDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    edConf *pp = (edConf *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getStatus());
        case 1: return ulong2string(pp->getEnergyLevel());
        default: return "";
    }
}

bool edConfDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    edConf *pp = (edConf *)object; (void)pp;
    switch (field) {
        case 0: pp->setStatus(string2ulong(value)); return true;
        case 1: pp->setEnergyLevel(string2ulong(value)); return true;
        default: return false;
    }
}

const char *edConfDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *edConfDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    edConf *pp = (edConf *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


