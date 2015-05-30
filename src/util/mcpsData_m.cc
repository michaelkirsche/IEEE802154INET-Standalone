//
// Generated file, do not edit! Created by nedtool 4.6 from util/mcpsData.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "mcpsData_m.h"

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

Register_Class(mcpsDataReq);

mcpsDataReq::mcpsDataReq(const char *name, int kind) : ::cPacket(name,kind)
{
    this->SrcAddrMode_var = 0;
    this->DstAddrMode_var = 0;
    this->DstPANId_var = 0;
    this->msduLength_var = 0;
    this->msduHandle_var = 0;
    this->TxOptions_var = 0;
    this->SecurityLevel_var = 0;
    this->KeyIdMode_var = 0;
    this->KeySource_var = 0;
    this->KeyIndex_var = 0;
}

mcpsDataReq::mcpsDataReq(const mcpsDataReq& other) : ::cPacket(other)
{
    copy(other);
}

mcpsDataReq::~mcpsDataReq()
{
}

mcpsDataReq& mcpsDataReq::operator=(const mcpsDataReq& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void mcpsDataReq::copy(const mcpsDataReq& other)
{
    this->SrcAddrMode_var = other.SrcAddrMode_var;
    this->DstAddrMode_var = other.DstAddrMode_var;
    this->DstPANId_var = other.DstPANId_var;
    this->DstAddr_var = other.DstAddr_var;
    this->msduLength_var = other.msduLength_var;
    this->msduHandle_var = other.msduHandle_var;
    this->TxOptions_var = other.TxOptions_var;
    this->SecurityLevel_var = other.SecurityLevel_var;
    this->KeyIdMode_var = other.KeyIdMode_var;
    this->KeySource_var = other.KeySource_var;
    this->KeyIndex_var = other.KeyIndex_var;
}

void mcpsDataReq::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->SrcAddrMode_var);
    doPacking(b,this->DstAddrMode_var);
    doPacking(b,this->DstPANId_var);
    doPacking(b,this->DstAddr_var);
    doPacking(b,this->msduLength_var);
    doPacking(b,this->msduHandle_var);
    doPacking(b,this->TxOptions_var);
    doPacking(b,this->SecurityLevel_var);
    doPacking(b,this->KeyIdMode_var);
    doPacking(b,this->KeySource_var);
    doPacking(b,this->KeyIndex_var);
}

void mcpsDataReq::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->SrcAddrMode_var);
    doUnpacking(b,this->DstAddrMode_var);
    doUnpacking(b,this->DstPANId_var);
    doUnpacking(b,this->DstAddr_var);
    doUnpacking(b,this->msduLength_var);
    doUnpacking(b,this->msduHandle_var);
    doUnpacking(b,this->TxOptions_var);
    doUnpacking(b,this->SecurityLevel_var);
    doUnpacking(b,this->KeyIdMode_var);
    doUnpacking(b,this->KeySource_var);
    doUnpacking(b,this->KeyIndex_var);
}

unsigned char mcpsDataReq::getSrcAddrMode() const
{
    return SrcAddrMode_var;
}

void mcpsDataReq::setSrcAddrMode(unsigned char SrcAddrMode)
{
    this->SrcAddrMode_var = SrcAddrMode;
}

unsigned char mcpsDataReq::getDstAddrMode() const
{
    return DstAddrMode_var;
}

void mcpsDataReq::setDstAddrMode(unsigned char DstAddrMode)
{
    this->DstAddrMode_var = DstAddrMode;
}

unsigned short mcpsDataReq::getDstPANId() const
{
    return DstPANId_var;
}

void mcpsDataReq::setDstPANId(unsigned short DstPANId)
{
    this->DstPANId_var = DstPANId;
}

MACAddressExt& mcpsDataReq::getDstAddr()
{
    return DstAddr_var;
}

void mcpsDataReq::setDstAddr(const MACAddressExt& DstAddr)
{
    this->DstAddr_var = DstAddr;
}

unsigned char mcpsDataReq::getMsduLength() const
{
    return msduLength_var;
}

void mcpsDataReq::setMsduLength(unsigned char msduLength)
{
    this->msduLength_var = msduLength;
}

unsigned long mcpsDataReq::getMsduHandle() const
{
    return msduHandle_var;
}

void mcpsDataReq::setMsduHandle(unsigned long msduHandle)
{
    this->msduHandle_var = msduHandle;
}

unsigned char mcpsDataReq::getTxOptions() const
{
    return TxOptions_var;
}

void mcpsDataReq::setTxOptions(unsigned char TxOptions)
{
    this->TxOptions_var = TxOptions;
}

unsigned char mcpsDataReq::getSecurityLevel() const
{
    return SecurityLevel_var;
}

void mcpsDataReq::setSecurityLevel(unsigned char SecurityLevel)
{
    this->SecurityLevel_var = SecurityLevel;
}

unsigned char mcpsDataReq::getKeyIdMode() const
{
    return KeyIdMode_var;
}

void mcpsDataReq::setKeyIdMode(unsigned char KeyIdMode)
{
    this->KeyIdMode_var = KeyIdMode;
}

unsigned long mcpsDataReq::getKeySource() const
{
    return KeySource_var;
}

void mcpsDataReq::setKeySource(unsigned long KeySource)
{
    this->KeySource_var = KeySource;
}

unsigned char mcpsDataReq::getKeyIndex() const
{
    return KeyIndex_var;
}

void mcpsDataReq::setKeyIndex(unsigned char KeyIndex)
{
    this->KeyIndex_var = KeyIndex;
}

class mcpsDataReqDescriptor : public cClassDescriptor
{
  public:
    mcpsDataReqDescriptor();
    virtual ~mcpsDataReqDescriptor();

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

Register_ClassDescriptor(mcpsDataReqDescriptor);

mcpsDataReqDescriptor::mcpsDataReqDescriptor() : cClassDescriptor("mcpsDataReq", "cPacket")
{
}

mcpsDataReqDescriptor::~mcpsDataReqDescriptor()
{
}

bool mcpsDataReqDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<mcpsDataReq *>(obj)!=NULL;
}

const char *mcpsDataReqDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int mcpsDataReqDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 11+basedesc->getFieldCount(object) : 11;
}

unsigned int mcpsDataReqDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<11) ? fieldTypeFlags[field] : 0;
}

const char *mcpsDataReqDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "SrcAddrMode",
        "DstAddrMode",
        "DstPANId",
        "DstAddr",
        "msduLength",
        "msduHandle",
        "TxOptions",
        "SecurityLevel",
        "KeyIdMode",
        "KeySource",
        "KeyIndex",
    };
    return (field>=0 && field<11) ? fieldNames[field] : NULL;
}

int mcpsDataReqDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='S' && strcmp(fieldName, "SrcAddrMode")==0) return base+0;
    if (fieldName[0]=='D' && strcmp(fieldName, "DstAddrMode")==0) return base+1;
    if (fieldName[0]=='D' && strcmp(fieldName, "DstPANId")==0) return base+2;
    if (fieldName[0]=='D' && strcmp(fieldName, "DstAddr")==0) return base+3;
    if (fieldName[0]=='m' && strcmp(fieldName, "msduLength")==0) return base+4;
    if (fieldName[0]=='m' && strcmp(fieldName, "msduHandle")==0) return base+5;
    if (fieldName[0]=='T' && strcmp(fieldName, "TxOptions")==0) return base+6;
    if (fieldName[0]=='S' && strcmp(fieldName, "SecurityLevel")==0) return base+7;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeyIdMode")==0) return base+8;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeySource")==0) return base+9;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeyIndex")==0) return base+10;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *mcpsDataReqDescriptor::getFieldTypeString(void *object, int field) const
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
        "unsigned short",
        "MACAddressExt",
        "unsigned char",
        "unsigned long",
        "unsigned char",
        "unsigned char",
        "unsigned char",
        "unsigned long",
        "unsigned char",
    };
    return (field>=0 && field<11) ? fieldTypeStrings[field] : NULL;
}

const char *mcpsDataReqDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "AddrMode";
            return NULL;
        default: return NULL;
    }
}

int mcpsDataReqDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    mcpsDataReq *pp = (mcpsDataReq *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string mcpsDataReqDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    mcpsDataReq *pp = (mcpsDataReq *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getSrcAddrMode());
        case 1: return ulong2string(pp->getDstAddrMode());
        case 2: return ulong2string(pp->getDstPANId());
        case 3: {std::stringstream out; out << pp->getDstAddr(); return out.str();}
        case 4: return ulong2string(pp->getMsduLength());
        case 5: return ulong2string(pp->getMsduHandle());
        case 6: return ulong2string(pp->getTxOptions());
        case 7: return ulong2string(pp->getSecurityLevel());
        case 8: return ulong2string(pp->getKeyIdMode());
        case 9: return ulong2string(pp->getKeySource());
        case 10: return ulong2string(pp->getKeyIndex());
        default: return "";
    }
}

bool mcpsDataReqDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    mcpsDataReq *pp = (mcpsDataReq *)object; (void)pp;
    switch (field) {
        case 0: pp->setSrcAddrMode(string2ulong(value)); return true;
        case 1: pp->setDstAddrMode(string2ulong(value)); return true;
        case 2: pp->setDstPANId(string2ulong(value)); return true;
        case 4: pp->setMsduLength(string2ulong(value)); return true;
        case 5: pp->setMsduHandle(string2ulong(value)); return true;
        case 6: pp->setTxOptions(string2ulong(value)); return true;
        case 7: pp->setSecurityLevel(string2ulong(value)); return true;
        case 8: pp->setKeyIdMode(string2ulong(value)); return true;
        case 9: pp->setKeySource(string2ulong(value)); return true;
        case 10: pp->setKeyIndex(string2ulong(value)); return true;
        default: return false;
    }
}

const char *mcpsDataReqDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 3: return opp_typename(typeid(MACAddressExt));
        default: return NULL;
    };
}

void *mcpsDataReqDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    mcpsDataReq *pp = (mcpsDataReq *)object; (void)pp;
    switch (field) {
        case 3: return (void *)(&pp->getDstAddr()); break;
        default: return NULL;
    }
}

Register_Class(mcpsDataInd);

mcpsDataInd::mcpsDataInd(const char *name, int kind) : ::mcpsDataReq(name,kind)
{
    this->SrcPANId_var = 0;
    this->mpduLinkQuality_var = 0;
    this->DSN_var = 0;
}

mcpsDataInd::mcpsDataInd(const mcpsDataInd& other) : ::mcpsDataReq(other)
{
    copy(other);
}

mcpsDataInd::~mcpsDataInd()
{
}

mcpsDataInd& mcpsDataInd::operator=(const mcpsDataInd& other)
{
    if (this==&other) return *this;
    ::mcpsDataReq::operator=(other);
    copy(other);
    return *this;
}

void mcpsDataInd::copy(const mcpsDataInd& other)
{
    this->SrcPANId_var = other.SrcPANId_var;
    this->SrcAddr_var = other.SrcAddr_var;
    this->mpduLinkQuality_var = other.mpduLinkQuality_var;
    this->DSN_var = other.DSN_var;
}

void mcpsDataInd::parsimPack(cCommBuffer *b)
{
    ::mcpsDataReq::parsimPack(b);
    doPacking(b,this->SrcPANId_var);
    doPacking(b,this->SrcAddr_var);
    doPacking(b,this->mpduLinkQuality_var);
    doPacking(b,this->DSN_var);
}

void mcpsDataInd::parsimUnpack(cCommBuffer *b)
{
    ::mcpsDataReq::parsimUnpack(b);
    doUnpacking(b,this->SrcPANId_var);
    doUnpacking(b,this->SrcAddr_var);
    doUnpacking(b,this->mpduLinkQuality_var);
    doUnpacking(b,this->DSN_var);
}

unsigned short mcpsDataInd::getSrcPANId() const
{
    return SrcPANId_var;
}

void mcpsDataInd::setSrcPANId(unsigned short SrcPANId)
{
    this->SrcPANId_var = SrcPANId;
}

MACAddressExt& mcpsDataInd::getSrcAddr()
{
    return SrcAddr_var;
}

void mcpsDataInd::setSrcAddr(const MACAddressExt& SrcAddr)
{
    this->SrcAddr_var = SrcAddr;
}

unsigned char mcpsDataInd::getMpduLinkQuality() const
{
    return mpduLinkQuality_var;
}

void mcpsDataInd::setMpduLinkQuality(unsigned char mpduLinkQuality)
{
    this->mpduLinkQuality_var = mpduLinkQuality;
}

unsigned char mcpsDataInd::getDSN() const
{
    return DSN_var;
}

void mcpsDataInd::setDSN(unsigned char DSN)
{
    this->DSN_var = DSN;
}

class mcpsDataIndDescriptor : public cClassDescriptor
{
  public:
    mcpsDataIndDescriptor();
    virtual ~mcpsDataIndDescriptor();

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

Register_ClassDescriptor(mcpsDataIndDescriptor);

mcpsDataIndDescriptor::mcpsDataIndDescriptor() : cClassDescriptor("mcpsDataInd", "mcpsDataReq")
{
}

mcpsDataIndDescriptor::~mcpsDataIndDescriptor()
{
}

bool mcpsDataIndDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<mcpsDataInd *>(obj)!=NULL;
}

const char *mcpsDataIndDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int mcpsDataIndDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int mcpsDataIndDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *mcpsDataIndDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "SrcPANId",
        "SrcAddr",
        "mpduLinkQuality",
        "DSN",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int mcpsDataIndDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='S' && strcmp(fieldName, "SrcPANId")==0) return base+0;
    if (fieldName[0]=='S' && strcmp(fieldName, "SrcAddr")==0) return base+1;
    if (fieldName[0]=='m' && strcmp(fieldName, "mpduLinkQuality")==0) return base+2;
    if (fieldName[0]=='D' && strcmp(fieldName, "DSN")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *mcpsDataIndDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
        "MACAddressExt",
        "unsigned char",
        "unsigned char",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *mcpsDataIndDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int mcpsDataIndDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    mcpsDataInd *pp = (mcpsDataInd *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string mcpsDataIndDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    mcpsDataInd *pp = (mcpsDataInd *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getSrcPANId());
        case 1: {std::stringstream out; out << pp->getSrcAddr(); return out.str();}
        case 2: return ulong2string(pp->getMpduLinkQuality());
        case 3: return ulong2string(pp->getDSN());
        default: return "";
    }
}

bool mcpsDataIndDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    mcpsDataInd *pp = (mcpsDataInd *)object; (void)pp;
    switch (field) {
        case 0: pp->setSrcPANId(string2ulong(value)); return true;
        case 2: pp->setMpduLinkQuality(string2ulong(value)); return true;
        case 3: pp->setDSN(string2ulong(value)); return true;
        default: return false;
    }
}

const char *mcpsDataIndDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 1: return opp_typename(typeid(MACAddressExt));
        default: return NULL;
    };
}

void *mcpsDataIndDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    mcpsDataInd *pp = (mcpsDataInd *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getSrcAddr()); break;
        default: return NULL;
    }
}

Register_Class(mcpsDataConf);

mcpsDataConf::mcpsDataConf(const char *name, int kind) : ::cPacket(name,kind)
{
    this->msduHandle_var = 0;
    this->status_var = 0;
}

mcpsDataConf::mcpsDataConf(const mcpsDataConf& other) : ::cPacket(other)
{
    copy(other);
}

mcpsDataConf::~mcpsDataConf()
{
}

mcpsDataConf& mcpsDataConf::operator=(const mcpsDataConf& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void mcpsDataConf::copy(const mcpsDataConf& other)
{
    this->msduHandle_var = other.msduHandle_var;
    this->status_var = other.status_var;
}

void mcpsDataConf::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->msduHandle_var);
    doPacking(b,this->status_var);
}

void mcpsDataConf::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->msduHandle_var);
    doUnpacking(b,this->status_var);
}

unsigned long mcpsDataConf::getMsduHandle() const
{
    return msduHandle_var;
}

void mcpsDataConf::setMsduHandle(unsigned long msduHandle)
{
    this->msduHandle_var = msduHandle;
}

unsigned char mcpsDataConf::getStatus() const
{
    return status_var;
}

void mcpsDataConf::setStatus(unsigned char status)
{
    this->status_var = status;
}

class mcpsDataConfDescriptor : public cClassDescriptor
{
  public:
    mcpsDataConfDescriptor();
    virtual ~mcpsDataConfDescriptor();

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

Register_ClassDescriptor(mcpsDataConfDescriptor);

mcpsDataConfDescriptor::mcpsDataConfDescriptor() : cClassDescriptor("mcpsDataConf", "cPacket")
{
}

mcpsDataConfDescriptor::~mcpsDataConfDescriptor()
{
}

bool mcpsDataConfDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<mcpsDataConf *>(obj)!=NULL;
}

const char *mcpsDataConfDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int mcpsDataConfDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int mcpsDataConfDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *mcpsDataConfDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "msduHandle",
        "status",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int mcpsDataConfDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "msduHandle")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *mcpsDataConfDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned long",
        "unsigned char",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *mcpsDataConfDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 1:
            if (!strcmp(propertyname,"enum")) return "MCPSStatus";
            return NULL;
        default: return NULL;
    }
}

int mcpsDataConfDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    mcpsDataConf *pp = (mcpsDataConf *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string mcpsDataConfDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    mcpsDataConf *pp = (mcpsDataConf *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getMsduHandle());
        case 1: return ulong2string(pp->getStatus());
        default: return "";
    }
}

bool mcpsDataConfDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    mcpsDataConf *pp = (mcpsDataConf *)object; (void)pp;
    switch (field) {
        case 0: pp->setMsduHandle(string2ulong(value)); return true;
        case 1: pp->setStatus(string2ulong(value)); return true;
        default: return false;
    }
}

const char *mcpsDataConfDescriptor::getFieldStructName(void *object, int field) const
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

void *mcpsDataConfDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    mcpsDataConf *pp = (mcpsDataConf *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(MaUnitdata);

MaUnitdata::MaUnitdata(const char *name, int kind) : ::cPacket(name,kind)
{
}

MaUnitdata::MaUnitdata(const MaUnitdata& other) : ::cPacket(other)
{
    copy(other);
}

MaUnitdata::~MaUnitdata()
{
}

MaUnitdata& MaUnitdata::operator=(const MaUnitdata& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void MaUnitdata::copy(const MaUnitdata& other)
{
    this->SrcAddr_var = other.SrcAddr_var;
    this->DstAddr_var = other.DstAddr_var;
}

void MaUnitdata::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->SrcAddr_var);
    doPacking(b,this->DstAddr_var);
}

void MaUnitdata::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->SrcAddr_var);
    doUnpacking(b,this->DstAddr_var);
}

MACAddressExt& MaUnitdata::getSrcAddr()
{
    return SrcAddr_var;
}

void MaUnitdata::setSrcAddr(const MACAddressExt& SrcAddr)
{
    this->SrcAddr_var = SrcAddr;
}

MACAddressExt& MaUnitdata::getDstAddr()
{
    return DstAddr_var;
}

void MaUnitdata::setDstAddr(const MACAddressExt& DstAddr)
{
    this->DstAddr_var = DstAddr;
}

class MaUnitdataDescriptor : public cClassDescriptor
{
  public:
    MaUnitdataDescriptor();
    virtual ~MaUnitdataDescriptor();

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

Register_ClassDescriptor(MaUnitdataDescriptor);

MaUnitdataDescriptor::MaUnitdataDescriptor() : cClassDescriptor("MaUnitdata", "cPacket")
{
}

MaUnitdataDescriptor::~MaUnitdataDescriptor()
{
}

bool MaUnitdataDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<MaUnitdata *>(obj)!=NULL;
}

const char *MaUnitdataDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int MaUnitdataDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int MaUnitdataDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *MaUnitdataDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "SrcAddr",
        "DstAddr",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int MaUnitdataDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='S' && strcmp(fieldName, "SrcAddr")==0) return base+0;
    if (fieldName[0]=='D' && strcmp(fieldName, "DstAddr")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *MaUnitdataDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "MACAddressExt",
        "MACAddressExt",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *MaUnitdataDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int MaUnitdataDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    MaUnitdata *pp = (MaUnitdata *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string MaUnitdataDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    MaUnitdata *pp = (MaUnitdata *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getSrcAddr(); return out.str();}
        case 1: {std::stringstream out; out << pp->getDstAddr(); return out.str();}
        default: return "";
    }
}

bool MaUnitdataDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    MaUnitdata *pp = (MaUnitdata *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *MaUnitdataDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(MACAddressExt));
        case 1: return opp_typename(typeid(MACAddressExt));
        default: return NULL;
    };
}

void *MaUnitdataDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    MaUnitdata *pp = (MaUnitdata *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getSrcAddr()); break;
        case 1: return (void *)(&pp->getDstAddr()); break;
        default: return NULL;
    }
}

Register_Class(mcpsPurgeReq);

mcpsPurgeReq::mcpsPurgeReq(const char *name, int kind) : ::cMessage(name,kind)
{
    this->msduHandle_var = 0;
}

mcpsPurgeReq::mcpsPurgeReq(const mcpsPurgeReq& other) : ::cMessage(other)
{
    copy(other);
}

mcpsPurgeReq::~mcpsPurgeReq()
{
}

mcpsPurgeReq& mcpsPurgeReq::operator=(const mcpsPurgeReq& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void mcpsPurgeReq::copy(const mcpsPurgeReq& other)
{
    this->msduHandle_var = other.msduHandle_var;
}

void mcpsPurgeReq::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->msduHandle_var);
}

void mcpsPurgeReq::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->msduHandle_var);
}

unsigned long mcpsPurgeReq::getMsduHandle() const
{
    return msduHandle_var;
}

void mcpsPurgeReq::setMsduHandle(unsigned long msduHandle)
{
    this->msduHandle_var = msduHandle;
}

class mcpsPurgeReqDescriptor : public cClassDescriptor
{
  public:
    mcpsPurgeReqDescriptor();
    virtual ~mcpsPurgeReqDescriptor();

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

Register_ClassDescriptor(mcpsPurgeReqDescriptor);

mcpsPurgeReqDescriptor::mcpsPurgeReqDescriptor() : cClassDescriptor("mcpsPurgeReq", "cMessage")
{
}

mcpsPurgeReqDescriptor::~mcpsPurgeReqDescriptor()
{
}

bool mcpsPurgeReqDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<mcpsPurgeReq *>(obj)!=NULL;
}

const char *mcpsPurgeReqDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int mcpsPurgeReqDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int mcpsPurgeReqDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *mcpsPurgeReqDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "msduHandle",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int mcpsPurgeReqDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "msduHandle")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *mcpsPurgeReqDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned long",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *mcpsPurgeReqDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int mcpsPurgeReqDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    mcpsPurgeReq *pp = (mcpsPurgeReq *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string mcpsPurgeReqDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    mcpsPurgeReq *pp = (mcpsPurgeReq *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getMsduHandle());
        default: return "";
    }
}

bool mcpsPurgeReqDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    mcpsPurgeReq *pp = (mcpsPurgeReq *)object; (void)pp;
    switch (field) {
        case 0: pp->setMsduHandle(string2ulong(value)); return true;
        default: return false;
    }
}

const char *mcpsPurgeReqDescriptor::getFieldStructName(void *object, int field) const
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

void *mcpsPurgeReqDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    mcpsPurgeReq *pp = (mcpsPurgeReq *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(mcpsPurgeConf);

mcpsPurgeConf::mcpsPurgeConf(const char *name, int kind) : ::mcpsPurgeReq(name,kind)
{
    this->status_var = 0;
}

mcpsPurgeConf::mcpsPurgeConf(const mcpsPurgeConf& other) : ::mcpsPurgeReq(other)
{
    copy(other);
}

mcpsPurgeConf::~mcpsPurgeConf()
{
}

mcpsPurgeConf& mcpsPurgeConf::operator=(const mcpsPurgeConf& other)
{
    if (this==&other) return *this;
    ::mcpsPurgeReq::operator=(other);
    copy(other);
    return *this;
}

void mcpsPurgeConf::copy(const mcpsPurgeConf& other)
{
    this->status_var = other.status_var;
}

void mcpsPurgeConf::parsimPack(cCommBuffer *b)
{
    ::mcpsPurgeReq::parsimPack(b);
    doPacking(b,this->status_var);
}

void mcpsPurgeConf::parsimUnpack(cCommBuffer *b)
{
    ::mcpsPurgeReq::parsimUnpack(b);
    doUnpacking(b,this->status_var);
}

unsigned char mcpsPurgeConf::getStatus() const
{
    return status_var;
}

void mcpsPurgeConf::setStatus(unsigned char status)
{
    this->status_var = status;
}

class mcpsPurgeConfDescriptor : public cClassDescriptor
{
  public:
    mcpsPurgeConfDescriptor();
    virtual ~mcpsPurgeConfDescriptor();

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

Register_ClassDescriptor(mcpsPurgeConfDescriptor);

mcpsPurgeConfDescriptor::mcpsPurgeConfDescriptor() : cClassDescriptor("mcpsPurgeConf", "mcpsPurgeReq")
{
}

mcpsPurgeConfDescriptor::~mcpsPurgeConfDescriptor()
{
}

bool mcpsPurgeConfDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<mcpsPurgeConf *>(obj)!=NULL;
}

const char *mcpsPurgeConfDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int mcpsPurgeConfDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int mcpsPurgeConfDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *mcpsPurgeConfDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "status",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int mcpsPurgeConfDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *mcpsPurgeConfDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *mcpsPurgeConfDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "purgeStatus";
            return NULL;
        default: return NULL;
    }
}

int mcpsPurgeConfDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    mcpsPurgeConf *pp = (mcpsPurgeConf *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string mcpsPurgeConfDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    mcpsPurgeConf *pp = (mcpsPurgeConf *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getStatus());
        default: return "";
    }
}

bool mcpsPurgeConfDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    mcpsPurgeConf *pp = (mcpsPurgeConf *)object; (void)pp;
    switch (field) {
        case 0: pp->setStatus(string2ulong(value)); return true;
        default: return false;
    }
}

const char *mcpsPurgeConfDescriptor::getFieldStructName(void *object, int field) const
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

void *mcpsPurgeConfDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    mcpsPurgeConf *pp = (mcpsPurgeConf *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


