//
// Generated file, do not edit! Created by nedtool 4.6 from util/MPDU.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "MPDU_m.h"

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

Register_Class(mpdu);

mpdu::mpdu(const char *name, int kind) : ::cPacket(name,kind)
{
    this->fcs_var = 0;
    this->srcPANid_var = 0;
    this->destPANid_var = 0;
    this->sqnr_var = 0;
    this->fcf_var = 0;
    this->isGTS_var = false;
    this->isIndirect_var = false;
}

mpdu::mpdu(const mpdu& other) : ::cPacket(other)
{
    copy(other);
}

mpdu::~mpdu()
{
}

mpdu& mpdu::operator=(const mpdu& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void mpdu::copy(const mpdu& other)
{
    this->fcs_var = other.fcs_var;
    this->ash_var = other.ash_var;
    this->src_var = other.src_var;
    this->srcPANid_var = other.srcPANid_var;
    this->dest_var = other.dest_var;
    this->destPANid_var = other.destPANid_var;
    this->sqnr_var = other.sqnr_var;
    this->fcf_var = other.fcf_var;
    this->isGTS_var = other.isGTS_var;
    this->isIndirect_var = other.isIndirect_var;
}

void mpdu::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->fcs_var);
    doPacking(b,this->ash_var);
    doPacking(b,this->src_var);
    doPacking(b,this->srcPANid_var);
    doPacking(b,this->dest_var);
    doPacking(b,this->destPANid_var);
    doPacking(b,this->sqnr_var);
    doPacking(b,this->fcf_var);
    doPacking(b,this->isGTS_var);
    doPacking(b,this->isIndirect_var);
}

void mpdu::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->fcs_var);
    doUnpacking(b,this->ash_var);
    doUnpacking(b,this->src_var);
    doUnpacking(b,this->srcPANid_var);
    doUnpacking(b,this->dest_var);
    doUnpacking(b,this->destPANid_var);
    doUnpacking(b,this->sqnr_var);
    doUnpacking(b,this->fcf_var);
    doUnpacking(b,this->isGTS_var);
    doUnpacking(b,this->isIndirect_var);
}

unsigned short mpdu::getFcs() const
{
    return fcs_var;
}

void mpdu::setFcs(unsigned short fcs)
{
    this->fcs_var = fcs;
}

Ash& mpdu::getAsh()
{
    return ash_var;
}

void mpdu::setAsh(const Ash& ash)
{
    this->ash_var = ash;
}

MACAddressExt& mpdu::getSrc()
{
    return src_var;
}

void mpdu::setSrc(const MACAddressExt& src)
{
    this->src_var = src;
}

unsigned short mpdu::getSrcPANid() const
{
    return srcPANid_var;
}

void mpdu::setSrcPANid(unsigned short srcPANid)
{
    this->srcPANid_var = srcPANid;
}

MACAddressExt& mpdu::getDest()
{
    return dest_var;
}

void mpdu::setDest(const MACAddressExt& dest)
{
    this->dest_var = dest;
}

unsigned short mpdu::getDestPANid() const
{
    return destPANid_var;
}

void mpdu::setDestPANid(unsigned short destPANid)
{
    this->destPANid_var = destPANid;
}

unsigned char mpdu::getSqnr() const
{
    return sqnr_var;
}

void mpdu::setSqnr(unsigned char sqnr)
{
    this->sqnr_var = sqnr;
}

unsigned short mpdu::getFcf() const
{
    return fcf_var;
}

void mpdu::setFcf(unsigned short fcf)
{
    this->fcf_var = fcf;
}

bool mpdu::getIsGTS() const
{
    return isGTS_var;
}

void mpdu::setIsGTS(bool isGTS)
{
    this->isGTS_var = isGTS;
}

bool mpdu::getIsIndirect() const
{
    return isIndirect_var;
}

void mpdu::setIsIndirect(bool isIndirect)
{
    this->isIndirect_var = isIndirect;
}

class mpduDescriptor : public cClassDescriptor
{
  public:
    mpduDescriptor();
    virtual ~mpduDescriptor();

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

Register_ClassDescriptor(mpduDescriptor);

mpduDescriptor::mpduDescriptor() : cClassDescriptor("mpdu", "cPacket")
{
}

mpduDescriptor::~mpduDescriptor()
{
}

bool mpduDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<mpdu *>(obj)!=NULL;
}

const char *mpduDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int mpduDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 10+basedesc->getFieldCount(object) : 10;
}

unsigned int mpduDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<10) ? fieldTypeFlags[field] : 0;
}

const char *mpduDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "fcs",
        "ash",
        "src",
        "srcPANid",
        "dest",
        "destPANid",
        "sqnr",
        "fcf",
        "isGTS",
        "isIndirect",
    };
    return (field>=0 && field<10) ? fieldNames[field] : NULL;
}

int mpduDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "fcs")==0) return base+0;
    if (fieldName[0]=='a' && strcmp(fieldName, "ash")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "src")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcPANid")==0) return base+3;
    if (fieldName[0]=='d' && strcmp(fieldName, "dest")==0) return base+4;
    if (fieldName[0]=='d' && strcmp(fieldName, "destPANid")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "sqnr")==0) return base+6;
    if (fieldName[0]=='f' && strcmp(fieldName, "fcf")==0) return base+7;
    if (fieldName[0]=='i' && strcmp(fieldName, "isGTS")==0) return base+8;
    if (fieldName[0]=='i' && strcmp(fieldName, "isIndirect")==0) return base+9;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *mpduDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
        "Ash",
        "MACAddressExt",
        "unsigned short",
        "MACAddressExt",
        "unsigned short",
        "unsigned char",
        "unsigned short",
        "bool",
        "bool",
    };
    return (field>=0 && field<10) ? fieldTypeStrings[field] : NULL;
}

const char *mpduDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int mpduDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    mpdu *pp = (mpdu *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string mpduDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    mpdu *pp = (mpdu *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getFcs());
        case 1: {std::stringstream out; out << pp->getAsh(); return out.str();}
        case 2: {std::stringstream out; out << pp->getSrc(); return out.str();}
        case 3: return ulong2string(pp->getSrcPANid());
        case 4: {std::stringstream out; out << pp->getDest(); return out.str();}
        case 5: return ulong2string(pp->getDestPANid());
        case 6: return ulong2string(pp->getSqnr());
        case 7: return ulong2string(pp->getFcf());
        case 8: return bool2string(pp->getIsGTS());
        case 9: return bool2string(pp->getIsIndirect());
        default: return "";
    }
}

bool mpduDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    mpdu *pp = (mpdu *)object; (void)pp;
    switch (field) {
        case 0: pp->setFcs(string2ulong(value)); return true;
        case 3: pp->setSrcPANid(string2ulong(value)); return true;
        case 5: pp->setDestPANid(string2ulong(value)); return true;
        case 6: pp->setSqnr(string2ulong(value)); return true;
        case 7: pp->setFcf(string2ulong(value)); return true;
        case 8: pp->setIsGTS(string2bool(value)); return true;
        case 9: pp->setIsIndirect(string2bool(value)); return true;
        default: return false;
    }
}

const char *mpduDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 1: return opp_typename(typeid(Ash));
        case 2: return opp_typename(typeid(MACAddressExt));
        case 4: return opp_typename(typeid(MACAddressExt));
        default: return NULL;
    };
}

void *mpduDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    mpdu *pp = (mpdu *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getAsh()); break;
        case 2: return (void *)(&pp->getSrc()); break;
        case 4: return (void *)(&pp->getDest()); break;
        default: return NULL;
    }
}

Register_Class(beaconFrame);

beaconFrame::beaconFrame(const char *name, int kind) : ::mpdu(name,kind)
{
}

beaconFrame::beaconFrame(const beaconFrame& other) : ::mpdu(other)
{
    copy(other);
}

beaconFrame::~beaconFrame()
{
}

beaconFrame& beaconFrame::operator=(const beaconFrame& other)
{
    if (this==&other) return *this;
    ::mpdu::operator=(other);
    copy(other);
    return *this;
}

void beaconFrame::copy(const beaconFrame& other)
{
    this->sfSpec_var = other.sfSpec_var;
    for (unsigned int i=0; i<7; i++)
        this->gtsList_var[i] = other.gtsList_var[i];
    this->paFields_var = other.paFields_var;
}

void beaconFrame::parsimPack(cCommBuffer *b)
{
    ::mpdu::parsimPack(b);
    doPacking(b,this->sfSpec_var);
    doPacking(b,this->gtsList_var,7);
    doPacking(b,this->paFields_var);
}

void beaconFrame::parsimUnpack(cCommBuffer *b)
{
    ::mpdu::parsimUnpack(b);
    doUnpacking(b,this->sfSpec_var);
    doUnpacking(b,this->gtsList_var,7);
    doUnpacking(b,this->paFields_var);
}

SuperframeSpec& beaconFrame::getSfSpec()
{
    return sfSpec_var;
}

void beaconFrame::setSfSpec(const SuperframeSpec& sfSpec)
{
    this->sfSpec_var = sfSpec;
}

unsigned int beaconFrame::getGtsListArraySize() const
{
    return 7;
}

GTSDescriptor& beaconFrame::getGtsList(unsigned int k)
{
    if (k>=7) throw cRuntimeError("Array of size 7 indexed by %lu", (unsigned long)k);
    return gtsList_var[k];
}

void beaconFrame::setGtsList(unsigned int k, const GTSDescriptor& gtsList)
{
    if (k>=7) throw cRuntimeError("Array of size 7 indexed by %lu", (unsigned long)k);
    this->gtsList_var[k] = gtsList;
}

PendingAddrFields& beaconFrame::getPaFields()
{
    return paFields_var;
}

void beaconFrame::setPaFields(const PendingAddrFields& paFields)
{
    this->paFields_var = paFields;
}

class beaconFrameDescriptor : public cClassDescriptor
{
  public:
    beaconFrameDescriptor();
    virtual ~beaconFrameDescriptor();

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

Register_ClassDescriptor(beaconFrameDescriptor);

beaconFrameDescriptor::beaconFrameDescriptor() : cClassDescriptor("beaconFrame", "mpdu")
{
}

beaconFrameDescriptor::~beaconFrameDescriptor()
{
}

bool beaconFrameDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<beaconFrame *>(obj)!=NULL;
}

const char *beaconFrameDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int beaconFrameDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int beaconFrameDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISARRAY | FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *beaconFrameDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "sfSpec",
        "gtsList",
        "paFields",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int beaconFrameDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sfSpec")==0) return base+0;
    if (fieldName[0]=='g' && strcmp(fieldName, "gtsList")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "paFields")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *beaconFrameDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "SuperframeSpec",
        "GTSDescriptor",
        "PendingAddrFields",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *beaconFrameDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int beaconFrameDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    beaconFrame *pp = (beaconFrame *)object; (void)pp;
    switch (field) {
        case 1: return 7;
        default: return 0;
    }
}

std::string beaconFrameDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    beaconFrame *pp = (beaconFrame *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getSfSpec(); return out.str();}
        case 1: {std::stringstream out; out << pp->getGtsList(i); return out.str();}
        case 2: {std::stringstream out; out << pp->getPaFields(); return out.str();}
        default: return "";
    }
}

bool beaconFrameDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    beaconFrame *pp = (beaconFrame *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *beaconFrameDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(SuperframeSpec));
        case 1: return opp_typename(typeid(GTSDescriptor));
        case 2: return opp_typename(typeid(PendingAddrFields));
        default: return NULL;
    };
}

void *beaconFrameDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    beaconFrame *pp = (beaconFrame *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getSfSpec()); break;
        case 1: return (void *)(&pp->getGtsList(i)); break;
        case 2: return (void *)(&pp->getPaFields()); break;
        default: return NULL;
    }
}

Register_Class(beaconNotify);

beaconNotify::beaconNotify(const char *name, int kind) : ::cPacket(name,kind)
{
    this->BSN_var = 0;
    this->sduLength_var = 0;
}

beaconNotify::beaconNotify(const beaconNotify& other) : ::cPacket(other)
{
    copy(other);
}

beaconNotify::~beaconNotify()
{
}

beaconNotify& beaconNotify::operator=(const beaconNotify& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void beaconNotify::copy(const beaconNotify& other)
{
    this->BSN_var = other.BSN_var;
    this->PANDescriptor_var = other.PANDescriptor_var;
    this->PendAddrSpec_var = other.PendAddrSpec_var;
    this->sduLength_var = other.sduLength_var;
}

void beaconNotify::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->BSN_var);
    doPacking(b,this->PANDescriptor_var);
    doPacking(b,this->PendAddrSpec_var);
    doPacking(b,this->sduLength_var);
}

void beaconNotify::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->BSN_var);
    doUnpacking(b,this->PANDescriptor_var);
    doUnpacking(b,this->PendAddrSpec_var);
    doUnpacking(b,this->sduLength_var);
}

unsigned char beaconNotify::getBSN() const
{
    return BSN_var;
}

void beaconNotify::setBSN(unsigned char BSN)
{
    this->BSN_var = BSN;
}

PAN_ELE& beaconNotify::getPANDescriptor()
{
    return PANDescriptor_var;
}

void beaconNotify::setPANDescriptor(const PAN_ELE& PANDescriptor)
{
    this->PANDescriptor_var = PANDescriptor;
}

PendingAddrFields& beaconNotify::getPendAddrSpec()
{
    return PendAddrSpec_var;
}

void beaconNotify::setPendAddrSpec(const PendingAddrFields& PendAddrSpec)
{
    this->PendAddrSpec_var = PendAddrSpec;
}

unsigned char beaconNotify::getSduLength() const
{
    return sduLength_var;
}

void beaconNotify::setSduLength(unsigned char sduLength)
{
    this->sduLength_var = sduLength;
}

class beaconNotifyDescriptor : public cClassDescriptor
{
  public:
    beaconNotifyDescriptor();
    virtual ~beaconNotifyDescriptor();

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

Register_ClassDescriptor(beaconNotifyDescriptor);

beaconNotifyDescriptor::beaconNotifyDescriptor() : cClassDescriptor("beaconNotify", "cPacket")
{
}

beaconNotifyDescriptor::~beaconNotifyDescriptor()
{
}

bool beaconNotifyDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<beaconNotify *>(obj)!=NULL;
}

const char *beaconNotifyDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int beaconNotifyDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int beaconNotifyDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *beaconNotifyDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "BSN",
        "PANDescriptor",
        "PendAddrSpec",
        "sduLength",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int beaconNotifyDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='B' && strcmp(fieldName, "BSN")==0) return base+0;
    if (fieldName[0]=='P' && strcmp(fieldName, "PANDescriptor")==0) return base+1;
    if (fieldName[0]=='P' && strcmp(fieldName, "PendAddrSpec")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "sduLength")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *beaconNotifyDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "PAN_ELE",
        "PendingAddrFields",
        "unsigned char",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *beaconNotifyDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int beaconNotifyDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    beaconNotify *pp = (beaconNotify *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string beaconNotifyDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    beaconNotify *pp = (beaconNotify *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getBSN());
        case 1: {std::stringstream out; out << pp->getPANDescriptor(); return out.str();}
        case 2: {std::stringstream out; out << pp->getPendAddrSpec(); return out.str();}
        case 3: return ulong2string(pp->getSduLength());
        default: return "";
    }
}

bool beaconNotifyDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    beaconNotify *pp = (beaconNotify *)object; (void)pp;
    switch (field) {
        case 0: pp->setBSN(string2ulong(value)); return true;
        case 3: pp->setSduLength(string2ulong(value)); return true;
        default: return false;
    }
}

const char *beaconNotifyDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 1: return opp_typename(typeid(PAN_ELE));
        case 2: return opp_typename(typeid(PendingAddrFields));
        default: return NULL;
    };
}

void *beaconNotifyDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    beaconNotify *pp = (beaconNotify *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getPANDescriptor()); break;
        case 2: return (void *)(&pp->getPendAddrSpec()); break;
        default: return NULL;
    }
}

Register_Class(CmdFrame);

CmdFrame::CmdFrame(const char *name, int kind) : ::mpdu(name,kind)
{
    this->cmdType_var = 0;
}

CmdFrame::CmdFrame(const CmdFrame& other) : ::mpdu(other)
{
    copy(other);
}

CmdFrame::~CmdFrame()
{
}

CmdFrame& CmdFrame::operator=(const CmdFrame& other)
{
    if (this==&other) return *this;
    ::mpdu::operator=(other);
    copy(other);
    return *this;
}

void CmdFrame::copy(const CmdFrame& other)
{
    this->cmdType_var = other.cmdType_var;
}

void CmdFrame::parsimPack(cCommBuffer *b)
{
    ::mpdu::parsimPack(b);
    doPacking(b,this->cmdType_var);
}

void CmdFrame::parsimUnpack(cCommBuffer *b)
{
    ::mpdu::parsimUnpack(b);
    doUnpacking(b,this->cmdType_var);
}

int CmdFrame::getCmdType() const
{
    return cmdType_var;
}

void CmdFrame::setCmdType(int cmdType)
{
    this->cmdType_var = cmdType;
}

class CmdFrameDescriptor : public cClassDescriptor
{
  public:
    CmdFrameDescriptor();
    virtual ~CmdFrameDescriptor();

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

Register_ClassDescriptor(CmdFrameDescriptor);

CmdFrameDescriptor::CmdFrameDescriptor() : cClassDescriptor("CmdFrame", "mpdu")
{
}

CmdFrameDescriptor::~CmdFrameDescriptor()
{
}

bool CmdFrameDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CmdFrame *>(obj)!=NULL;
}

const char *CmdFrameDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CmdFrameDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int CmdFrameDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *CmdFrameDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "cmdType",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int CmdFrameDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "cmdType")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CmdFrameDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *CmdFrameDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "Ieee802154MacCmdType";
            return NULL;
        default: return NULL;
    }
}

int CmdFrameDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CmdFrame *pp = (CmdFrame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CmdFrameDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CmdFrame *pp = (CmdFrame *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getCmdType());
        default: return "";
    }
}

bool CmdFrameDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CmdFrame *pp = (CmdFrame *)object; (void)pp;
    switch (field) {
        case 0: pp->setCmdType(string2long(value)); return true;
        default: return false;
    }
}

const char *CmdFrameDescriptor::getFieldStructName(void *object, int field) const
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

void *CmdFrameDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CmdFrame *pp = (CmdFrame *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(RealignCmd);

RealignCmd::RealignCmd(const char *name, int kind) : ::CmdFrame(name,kind)
{
    this->PANId_var = 0;
    this->CoordShortAddr_var = 0;
    this->LogicalChannel_var = 0;
    this->ShortAddr_var = 0;
    this->ChannelPage_var = 0;
}

RealignCmd::RealignCmd(const RealignCmd& other) : ::CmdFrame(other)
{
    copy(other);
}

RealignCmd::~RealignCmd()
{
}

RealignCmd& RealignCmd::operator=(const RealignCmd& other)
{
    if (this==&other) return *this;
    ::CmdFrame::operator=(other);
    copy(other);
    return *this;
}

void RealignCmd::copy(const RealignCmd& other)
{
    this->PANId_var = other.PANId_var;
    this->CoordShortAddr_var = other.CoordShortAddr_var;
    this->LogicalChannel_var = other.LogicalChannel_var;
    this->ShortAddr_var = other.ShortAddr_var;
    this->ChannelPage_var = other.ChannelPage_var;
}

void RealignCmd::parsimPack(cCommBuffer *b)
{
    ::CmdFrame::parsimPack(b);
    doPacking(b,this->PANId_var);
    doPacking(b,this->CoordShortAddr_var);
    doPacking(b,this->LogicalChannel_var);
    doPacking(b,this->ShortAddr_var);
    doPacking(b,this->ChannelPage_var);
}

void RealignCmd::parsimUnpack(cCommBuffer *b)
{
    ::CmdFrame::parsimUnpack(b);
    doUnpacking(b,this->PANId_var);
    doUnpacking(b,this->CoordShortAddr_var);
    doUnpacking(b,this->LogicalChannel_var);
    doUnpacking(b,this->ShortAddr_var);
    doUnpacking(b,this->ChannelPage_var);
}

unsigned short RealignCmd::getPANId() const
{
    return PANId_var;
}

void RealignCmd::setPANId(unsigned short PANId)
{
    this->PANId_var = PANId;
}

unsigned short RealignCmd::getCoordShortAddr() const
{
    return CoordShortAddr_var;
}

void RealignCmd::setCoordShortAddr(unsigned short CoordShortAddr)
{
    this->CoordShortAddr_var = CoordShortAddr;
}

unsigned int RealignCmd::getLogicalChannel() const
{
    return LogicalChannel_var;
}

void RealignCmd::setLogicalChannel(unsigned int LogicalChannel)
{
    this->LogicalChannel_var = LogicalChannel;
}

unsigned short RealignCmd::getShortAddr() const
{
    return ShortAddr_var;
}

void RealignCmd::setShortAddr(unsigned short ShortAddr)
{
    this->ShortAddr_var = ShortAddr;
}

unsigned char RealignCmd::getChannelPage() const
{
    return ChannelPage_var;
}

void RealignCmd::setChannelPage(unsigned char ChannelPage)
{
    this->ChannelPage_var = ChannelPage;
}

class RealignCmdDescriptor : public cClassDescriptor
{
  public:
    RealignCmdDescriptor();
    virtual ~RealignCmdDescriptor();

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

Register_ClassDescriptor(RealignCmdDescriptor);

RealignCmdDescriptor::RealignCmdDescriptor() : cClassDescriptor("RealignCmd", "CmdFrame")
{
}

RealignCmdDescriptor::~RealignCmdDescriptor()
{
}

bool RealignCmdDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<RealignCmd *>(obj)!=NULL;
}

const char *RealignCmdDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int RealignCmdDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int RealignCmdDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *RealignCmdDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "PANId",
        "CoordShortAddr",
        "LogicalChannel",
        "ShortAddr",
        "ChannelPage",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int RealignCmdDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='P' && strcmp(fieldName, "PANId")==0) return base+0;
    if (fieldName[0]=='C' && strcmp(fieldName, "CoordShortAddr")==0) return base+1;
    if (fieldName[0]=='L' && strcmp(fieldName, "LogicalChannel")==0) return base+2;
    if (fieldName[0]=='S' && strcmp(fieldName, "ShortAddr")==0) return base+3;
    if (fieldName[0]=='C' && strcmp(fieldName, "ChannelPage")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *RealignCmdDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
        "unsigned short",
        "unsigned int",
        "unsigned short",
        "unsigned char",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *RealignCmdDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int RealignCmdDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    RealignCmd *pp = (RealignCmd *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string RealignCmdDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    RealignCmd *pp = (RealignCmd *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getPANId());
        case 1: return ulong2string(pp->getCoordShortAddr());
        case 2: return ulong2string(pp->getLogicalChannel());
        case 3: return ulong2string(pp->getShortAddr());
        case 4: return ulong2string(pp->getChannelPage());
        default: return "";
    }
}

bool RealignCmdDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    RealignCmd *pp = (RealignCmd *)object; (void)pp;
    switch (field) {
        case 0: pp->setPANId(string2ulong(value)); return true;
        case 1: pp->setCoordShortAddr(string2ulong(value)); return true;
        case 2: pp->setLogicalChannel(string2ulong(value)); return true;
        case 3: pp->setShortAddr(string2ulong(value)); return true;
        case 4: pp->setChannelPage(string2ulong(value)); return true;
        default: return false;
    }
}

const char *RealignCmdDescriptor::getFieldStructName(void *object, int field) const
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

void *RealignCmdDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    RealignCmd *pp = (RealignCmd *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(GTSCmd);

GTSCmd::GTSCmd(const char *name, int kind) : ::CmdFrame(name,kind)
{
}

GTSCmd::GTSCmd(const GTSCmd& other) : ::CmdFrame(other)
{
    copy(other);
}

GTSCmd::~GTSCmd()
{
}

GTSCmd& GTSCmd::operator=(const GTSCmd& other)
{
    if (this==&other) return *this;
    ::CmdFrame::operator=(other);
    copy(other);
    return *this;
}

void GTSCmd::copy(const GTSCmd& other)
{
    this->GTSCharacteristics_var = other.GTSCharacteristics_var;
}

void GTSCmd::parsimPack(cCommBuffer *b)
{
    ::CmdFrame::parsimPack(b);
    doPacking(b,this->GTSCharacteristics_var);
}

void GTSCmd::parsimUnpack(cCommBuffer *b)
{
    ::CmdFrame::parsimUnpack(b);
    doUnpacking(b,this->GTSCharacteristics_var);
}

GTSDescriptor& GTSCmd::getGTSCharacteristics()
{
    return GTSCharacteristics_var;
}

void GTSCmd::setGTSCharacteristics(const GTSDescriptor& GTSCharacteristics)
{
    this->GTSCharacteristics_var = GTSCharacteristics;
}

class GTSCmdDescriptor : public cClassDescriptor
{
  public:
    GTSCmdDescriptor();
    virtual ~GTSCmdDescriptor();

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

Register_ClassDescriptor(GTSCmdDescriptor);

GTSCmdDescriptor::GTSCmdDescriptor() : cClassDescriptor("GTSCmd", "CmdFrame")
{
}

GTSCmdDescriptor::~GTSCmdDescriptor()
{
}

bool GTSCmdDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GTSCmd *>(obj)!=NULL;
}

const char *GTSCmdDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GTSCmdDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int GTSCmdDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *GTSCmdDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "GTSCharacteristics",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int GTSCmdDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='G' && strcmp(fieldName, "GTSCharacteristics")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GTSCmdDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "GTSDescriptor",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *GTSCmdDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int GTSCmdDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GTSCmd *pp = (GTSCmd *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GTSCmdDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GTSCmd *pp = (GTSCmd *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getGTSCharacteristics(); return out.str();}
        default: return "";
    }
}

bool GTSCmdDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GTSCmd *pp = (GTSCmd *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *GTSCmdDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(GTSDescriptor));
        default: return NULL;
    };
}

void *GTSCmdDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GTSCmd *pp = (GTSCmd *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getGTSCharacteristics()); break;
        default: return NULL;
    }
}

Register_Class(DisAssoCmd);

DisAssoCmd::DisAssoCmd(const char *name, int kind) : ::CmdFrame(name,kind)
{
    this->DisassociateReason_var = 0;
}

DisAssoCmd::DisAssoCmd(const DisAssoCmd& other) : ::CmdFrame(other)
{
    copy(other);
}

DisAssoCmd::~DisAssoCmd()
{
}

DisAssoCmd& DisAssoCmd::operator=(const DisAssoCmd& other)
{
    if (this==&other) return *this;
    ::CmdFrame::operator=(other);
    copy(other);
    return *this;
}

void DisAssoCmd::copy(const DisAssoCmd& other)
{
    this->DisassociateReason_var = other.DisassociateReason_var;
}

void DisAssoCmd::parsimPack(cCommBuffer *b)
{
    ::CmdFrame::parsimPack(b);
    doPacking(b,this->DisassociateReason_var);
}

void DisAssoCmd::parsimUnpack(cCommBuffer *b)
{
    ::CmdFrame::parsimUnpack(b);
    doUnpacking(b,this->DisassociateReason_var);
}

unsigned char DisAssoCmd::getDisassociateReason() const
{
    return DisassociateReason_var;
}

void DisAssoCmd::setDisassociateReason(unsigned char DisassociateReason)
{
    this->DisassociateReason_var = DisassociateReason;
}

class DisAssoCmdDescriptor : public cClassDescriptor
{
  public:
    DisAssoCmdDescriptor();
    virtual ~DisAssoCmdDescriptor();

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

Register_ClassDescriptor(DisAssoCmdDescriptor);

DisAssoCmdDescriptor::DisAssoCmdDescriptor() : cClassDescriptor("DisAssoCmd", "CmdFrame")
{
}

DisAssoCmdDescriptor::~DisAssoCmdDescriptor()
{
}

bool DisAssoCmdDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DisAssoCmd *>(obj)!=NULL;
}

const char *DisAssoCmdDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DisAssoCmdDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int DisAssoCmdDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *DisAssoCmdDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "DisassociateReason",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int DisAssoCmdDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='D' && strcmp(fieldName, "DisassociateReason")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DisAssoCmdDescriptor::getFieldTypeString(void *object, int field) const
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

const char *DisAssoCmdDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "DisAssociateReason";
            return NULL;
        default: return NULL;
    }
}

int DisAssoCmdDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DisAssoCmd *pp = (DisAssoCmd *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DisAssoCmdDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DisAssoCmd *pp = (DisAssoCmd *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getDisassociateReason());
        default: return "";
    }
}

bool DisAssoCmdDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DisAssoCmd *pp = (DisAssoCmd *)object; (void)pp;
    switch (field) {
        case 0: pp->setDisassociateReason(string2ulong(value)); return true;
        default: return false;
    }
}

const char *DisAssoCmdDescriptor::getFieldStructName(void *object, int field) const
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

void *DisAssoCmdDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DisAssoCmd *pp = (DisAssoCmd *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(AssoCmdreq);

AssoCmdreq::AssoCmdreq(const char *name, int kind) : ::CmdFrame(name,kind)
{
}

AssoCmdreq::AssoCmdreq(const AssoCmdreq& other) : ::CmdFrame(other)
{
    copy(other);
}

AssoCmdreq::~AssoCmdreq()
{
}

AssoCmdreq& AssoCmdreq::operator=(const AssoCmdreq& other)
{
    if (this==&other) return *this;
    ::CmdFrame::operator=(other);
    copy(other);
    return *this;
}

void AssoCmdreq::copy(const AssoCmdreq& other)
{
    this->CapabilityInformation_var = other.CapabilityInformation_var;
}

void AssoCmdreq::parsimPack(cCommBuffer *b)
{
    ::CmdFrame::parsimPack(b);
    doPacking(b,this->CapabilityInformation_var);
}

void AssoCmdreq::parsimUnpack(cCommBuffer *b)
{
    ::CmdFrame::parsimUnpack(b);
    doUnpacking(b,this->CapabilityInformation_var);
}

DevCapability& AssoCmdreq::getCapabilityInformation()
{
    return CapabilityInformation_var;
}

void AssoCmdreq::setCapabilityInformation(const DevCapability& CapabilityInformation)
{
    this->CapabilityInformation_var = CapabilityInformation;
}

class AssoCmdreqDescriptor : public cClassDescriptor
{
  public:
    AssoCmdreqDescriptor();
    virtual ~AssoCmdreqDescriptor();

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

Register_ClassDescriptor(AssoCmdreqDescriptor);

AssoCmdreqDescriptor::AssoCmdreqDescriptor() : cClassDescriptor("AssoCmdreq", "CmdFrame")
{
}

AssoCmdreqDescriptor::~AssoCmdreqDescriptor()
{
}

bool AssoCmdreqDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<AssoCmdreq *>(obj)!=NULL;
}

const char *AssoCmdreqDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int AssoCmdreqDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int AssoCmdreqDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *AssoCmdreqDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "CapabilityInformation",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int AssoCmdreqDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='C' && strcmp(fieldName, "CapabilityInformation")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *AssoCmdreqDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "DevCapability",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *AssoCmdreqDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int AssoCmdreqDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    AssoCmdreq *pp = (AssoCmdreq *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string AssoCmdreqDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    AssoCmdreq *pp = (AssoCmdreq *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getCapabilityInformation(); return out.str();}
        default: return "";
    }
}

bool AssoCmdreqDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    AssoCmdreq *pp = (AssoCmdreq *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *AssoCmdreqDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(DevCapability));
        default: return NULL;
    };
}

void *AssoCmdreqDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    AssoCmdreq *pp = (AssoCmdreq *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getCapabilityInformation()); break;
        default: return NULL;
    }
}

Register_Class(AssoCmdresp);

AssoCmdresp::AssoCmdresp(const char *name, int kind) : ::CmdFrame(name,kind)
{
    this->shortAddress_var = 0;
    this->status_var = 0;
}

AssoCmdresp::AssoCmdresp(const AssoCmdresp& other) : ::CmdFrame(other)
{
    copy(other);
}

AssoCmdresp::~AssoCmdresp()
{
}

AssoCmdresp& AssoCmdresp::operator=(const AssoCmdresp& other)
{
    if (this==&other) return *this;
    ::CmdFrame::operator=(other);
    copy(other);
    return *this;
}

void AssoCmdresp::copy(const AssoCmdresp& other)
{
    this->shortAddress_var = other.shortAddress_var;
    this->status_var = other.status_var;
}

void AssoCmdresp::parsimPack(cCommBuffer *b)
{
    ::CmdFrame::parsimPack(b);
    doPacking(b,this->shortAddress_var);
    doPacking(b,this->status_var);
}

void AssoCmdresp::parsimUnpack(cCommBuffer *b)
{
    ::CmdFrame::parsimUnpack(b);
    doUnpacking(b,this->shortAddress_var);
    doUnpacking(b,this->status_var);
}

unsigned short AssoCmdresp::getShortAddress() const
{
    return shortAddress_var;
}

void AssoCmdresp::setShortAddress(unsigned short shortAddress)
{
    this->shortAddress_var = shortAddress;
}

unsigned short AssoCmdresp::getStatus() const
{
    return status_var;
}

void AssoCmdresp::setStatus(unsigned short status)
{
    this->status_var = status;
}

class AssoCmdrespDescriptor : public cClassDescriptor
{
  public:
    AssoCmdrespDescriptor();
    virtual ~AssoCmdrespDescriptor();

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

Register_ClassDescriptor(AssoCmdrespDescriptor);

AssoCmdrespDescriptor::AssoCmdrespDescriptor() : cClassDescriptor("AssoCmdresp", "CmdFrame")
{
}

AssoCmdrespDescriptor::~AssoCmdrespDescriptor()
{
}

bool AssoCmdrespDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<AssoCmdresp *>(obj)!=NULL;
}

const char *AssoCmdrespDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int AssoCmdrespDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int AssoCmdrespDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *AssoCmdrespDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "shortAddress",
        "status",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int AssoCmdrespDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "shortAddress")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *AssoCmdrespDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
        "unsigned short",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *AssoCmdrespDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 1:
            if (!strcmp(propertyname,"enum")) return "MlmeAssociationStatus";
            return NULL;
        default: return NULL;
    }
}

int AssoCmdrespDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    AssoCmdresp *pp = (AssoCmdresp *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string AssoCmdrespDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    AssoCmdresp *pp = (AssoCmdresp *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getShortAddress());
        case 1: return ulong2string(pp->getStatus());
        default: return "";
    }
}

bool AssoCmdrespDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    AssoCmdresp *pp = (AssoCmdresp *)object; (void)pp;
    switch (field) {
        case 0: pp->setShortAddress(string2ulong(value)); return true;
        case 1: pp->setStatus(string2ulong(value)); return true;
        default: return false;
    }
}

const char *AssoCmdrespDescriptor::getFieldStructName(void *object, int field) const
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

void *AssoCmdrespDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    AssoCmdresp *pp = (AssoCmdresp *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(AckFrame);

AckFrame::AckFrame(const char *name, int kind) : ::cMessage(name,kind)
{
    this->fcs_var = 0;
    this->sqnr_var = 0;
    this->fcf_var = 0;
}

AckFrame::AckFrame(const AckFrame& other) : ::cMessage(other)
{
    copy(other);
}

AckFrame::~AckFrame()
{
}

AckFrame& AckFrame::operator=(const AckFrame& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void AckFrame::copy(const AckFrame& other)
{
    this->fcs_var = other.fcs_var;
    this->sqnr_var = other.sqnr_var;
    this->fcf_var = other.fcf_var;
}

void AckFrame::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->fcs_var);
    doPacking(b,this->sqnr_var);
    doPacking(b,this->fcf_var);
}

void AckFrame::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->fcs_var);
    doUnpacking(b,this->sqnr_var);
    doUnpacking(b,this->fcf_var);
}

unsigned short AckFrame::getFcs() const
{
    return fcs_var;
}

void AckFrame::setFcs(unsigned short fcs)
{
    this->fcs_var = fcs;
}

unsigned char AckFrame::getSqnr() const
{
    return sqnr_var;
}

void AckFrame::setSqnr(unsigned char sqnr)
{
    this->sqnr_var = sqnr;
}

unsigned short AckFrame::getFcf() const
{
    return fcf_var;
}

void AckFrame::setFcf(unsigned short fcf)
{
    this->fcf_var = fcf;
}

class AckFrameDescriptor : public cClassDescriptor
{
  public:
    AckFrameDescriptor();
    virtual ~AckFrameDescriptor();

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

Register_ClassDescriptor(AckFrameDescriptor);

AckFrameDescriptor::AckFrameDescriptor() : cClassDescriptor("AckFrame", "cMessage")
{
}

AckFrameDescriptor::~AckFrameDescriptor()
{
}

bool AckFrameDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<AckFrame *>(obj)!=NULL;
}

const char *AckFrameDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int AckFrameDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int AckFrameDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *AckFrameDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "fcs",
        "sqnr",
        "fcf",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int AckFrameDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "fcs")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sqnr")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "fcf")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *AckFrameDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
        "unsigned char",
        "unsigned short",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *AckFrameDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int AckFrameDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    AckFrame *pp = (AckFrame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string AckFrameDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    AckFrame *pp = (AckFrame *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getFcs());
        case 1: return ulong2string(pp->getSqnr());
        case 2: return ulong2string(pp->getFcf());
        default: return "";
    }
}

bool AckFrameDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    AckFrame *pp = (AckFrame *)object; (void)pp;
    switch (field) {
        case 0: pp->setFcs(string2ulong(value)); return true;
        case 1: pp->setSqnr(string2ulong(value)); return true;
        case 2: pp->setFcf(string2ulong(value)); return true;
        default: return false;
    }
}

const char *AckFrameDescriptor::getFieldStructName(void *object, int field) const
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

void *AckFrameDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    AckFrame *pp = (AckFrame *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(DisAssociation);

DisAssociation::DisAssociation(const char *name, int kind) : ::cMessage(name,kind)
{
    this->DeviceAddrMode_var = 0;
    this->DevicePANId_var = 0;
    this->DisassociateReason_var = 0;
    this->TxIndirect_var = 0;
    this->status_var = 0;
    this->SecurityLevel_var = 0;
    this->KeyIdMode_var = 0;
    this->KeySource_var = 0;
    this->KeyIndex_var = 0;
}

DisAssociation::DisAssociation(const DisAssociation& other) : ::cMessage(other)
{
    copy(other);
}

DisAssociation::~DisAssociation()
{
}

DisAssociation& DisAssociation::operator=(const DisAssociation& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void DisAssociation::copy(const DisAssociation& other)
{
    this->DeviceAddrMode_var = other.DeviceAddrMode_var;
    this->DevicePANId_var = other.DevicePANId_var;
    this->DeviceAddress_var = other.DeviceAddress_var;
    this->DisassociateReason_var = other.DisassociateReason_var;
    this->TxIndirect_var = other.TxIndirect_var;
    this->status_var = other.status_var;
    this->SecurityLevel_var = other.SecurityLevel_var;
    this->KeyIdMode_var = other.KeyIdMode_var;
    this->KeySource_var = other.KeySource_var;
    this->KeyIndex_var = other.KeyIndex_var;
}

void DisAssociation::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->DeviceAddrMode_var);
    doPacking(b,this->DevicePANId_var);
    doPacking(b,this->DeviceAddress_var);
    doPacking(b,this->DisassociateReason_var);
    doPacking(b,this->TxIndirect_var);
    doPacking(b,this->status_var);
    doPacking(b,this->SecurityLevel_var);
    doPacking(b,this->KeyIdMode_var);
    doPacking(b,this->KeySource_var);
    doPacking(b,this->KeyIndex_var);
}

void DisAssociation::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->DeviceAddrMode_var);
    doUnpacking(b,this->DevicePANId_var);
    doUnpacking(b,this->DeviceAddress_var);
    doUnpacking(b,this->DisassociateReason_var);
    doUnpacking(b,this->TxIndirect_var);
    doUnpacking(b,this->status_var);
    doUnpacking(b,this->SecurityLevel_var);
    doUnpacking(b,this->KeyIdMode_var);
    doUnpacking(b,this->KeySource_var);
    doUnpacking(b,this->KeyIndex_var);
}

unsigned char DisAssociation::getDeviceAddrMode() const
{
    return DeviceAddrMode_var;
}

void DisAssociation::setDeviceAddrMode(unsigned char DeviceAddrMode)
{
    this->DeviceAddrMode_var = DeviceAddrMode;
}

unsigned short DisAssociation::getDevicePANId() const
{
    return DevicePANId_var;
}

void DisAssociation::setDevicePANId(unsigned short DevicePANId)
{
    this->DevicePANId_var = DevicePANId;
}

MACAddressExt& DisAssociation::getDeviceAddress()
{
    return DeviceAddress_var;
}

void DisAssociation::setDeviceAddress(const MACAddressExt& DeviceAddress)
{
    this->DeviceAddress_var = DeviceAddress;
}

unsigned char DisAssociation::getDisassociateReason() const
{
    return DisassociateReason_var;
}

void DisAssociation::setDisassociateReason(unsigned char DisassociateReason)
{
    this->DisassociateReason_var = DisassociateReason;
}

bool DisAssociation::getTxIndirect() const
{
    return TxIndirect_var;
}

void DisAssociation::setTxIndirect(bool TxIndirect)
{
    this->TxIndirect_var = TxIndirect;
}

unsigned short DisAssociation::getStatus() const
{
    return status_var;
}

void DisAssociation::setStatus(unsigned short status)
{
    this->status_var = status;
}

unsigned char DisAssociation::getSecurityLevel() const
{
    return SecurityLevel_var;
}

void DisAssociation::setSecurityLevel(unsigned char SecurityLevel)
{
    this->SecurityLevel_var = SecurityLevel;
}

unsigned char DisAssociation::getKeyIdMode() const
{
    return KeyIdMode_var;
}

void DisAssociation::setKeyIdMode(unsigned char KeyIdMode)
{
    this->KeyIdMode_var = KeyIdMode;
}

unsigned long DisAssociation::getKeySource() const
{
    return KeySource_var;
}

void DisAssociation::setKeySource(unsigned long KeySource)
{
    this->KeySource_var = KeySource;
}

unsigned char DisAssociation::getKeyIndex() const
{
    return KeyIndex_var;
}

void DisAssociation::setKeyIndex(unsigned char KeyIndex)
{
    this->KeyIndex_var = KeyIndex;
}

class DisAssociationDescriptor : public cClassDescriptor
{
  public:
    DisAssociationDescriptor();
    virtual ~DisAssociationDescriptor();

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

Register_ClassDescriptor(DisAssociationDescriptor);

DisAssociationDescriptor::DisAssociationDescriptor() : cClassDescriptor("DisAssociation", "cMessage")
{
}

DisAssociationDescriptor::~DisAssociationDescriptor()
{
}

bool DisAssociationDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DisAssociation *>(obj)!=NULL;
}

const char *DisAssociationDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DisAssociationDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 10+basedesc->getFieldCount(object) : 10;
}

unsigned int DisAssociationDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<10) ? fieldTypeFlags[field] : 0;
}

const char *DisAssociationDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "DeviceAddrMode",
        "DevicePANId",
        "DeviceAddress",
        "DisassociateReason",
        "TxIndirect",
        "status",
        "SecurityLevel",
        "KeyIdMode",
        "KeySource",
        "KeyIndex",
    };
    return (field>=0 && field<10) ? fieldNames[field] : NULL;
}

int DisAssociationDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='D' && strcmp(fieldName, "DeviceAddrMode")==0) return base+0;
    if (fieldName[0]=='D' && strcmp(fieldName, "DevicePANId")==0) return base+1;
    if (fieldName[0]=='D' && strcmp(fieldName, "DeviceAddress")==0) return base+2;
    if (fieldName[0]=='D' && strcmp(fieldName, "DisassociateReason")==0) return base+3;
    if (fieldName[0]=='T' && strcmp(fieldName, "TxIndirect")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+5;
    if (fieldName[0]=='S' && strcmp(fieldName, "SecurityLevel")==0) return base+6;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeyIdMode")==0) return base+7;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeySource")==0) return base+8;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeyIndex")==0) return base+9;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DisAssociationDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "unsigned short",
        "MACAddressExt",
        "unsigned char",
        "bool",
        "unsigned short",
        "unsigned char",
        "unsigned char",
        "unsigned long",
        "unsigned char",
    };
    return (field>=0 && field<10) ? fieldTypeStrings[field] : NULL;
}

const char *DisAssociationDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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
        case 3:
            if (!strcmp(propertyname,"enum")) return "DisAssociateReason";
            return NULL;
        case 5:
            if (!strcmp(propertyname,"enum")) return "MACenum";
            return NULL;
        default: return NULL;
    }
}

int DisAssociationDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DisAssociation *pp = (DisAssociation *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DisAssociationDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DisAssociation *pp = (DisAssociation *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getDeviceAddrMode());
        case 1: return ulong2string(pp->getDevicePANId());
        case 2: {std::stringstream out; out << pp->getDeviceAddress(); return out.str();}
        case 3: return ulong2string(pp->getDisassociateReason());
        case 4: return bool2string(pp->getTxIndirect());
        case 5: return ulong2string(pp->getStatus());
        case 6: return ulong2string(pp->getSecurityLevel());
        case 7: return ulong2string(pp->getKeyIdMode());
        case 8: return ulong2string(pp->getKeySource());
        case 9: return ulong2string(pp->getKeyIndex());
        default: return "";
    }
}

bool DisAssociationDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DisAssociation *pp = (DisAssociation *)object; (void)pp;
    switch (field) {
        case 0: pp->setDeviceAddrMode(string2ulong(value)); return true;
        case 1: pp->setDevicePANId(string2ulong(value)); return true;
        case 3: pp->setDisassociateReason(string2ulong(value)); return true;
        case 4: pp->setTxIndirect(string2bool(value)); return true;
        case 5: pp->setStatus(string2ulong(value)); return true;
        case 6: pp->setSecurityLevel(string2ulong(value)); return true;
        case 7: pp->setKeyIdMode(string2ulong(value)); return true;
        case 8: pp->setKeySource(string2ulong(value)); return true;
        case 9: pp->setKeyIndex(string2ulong(value)); return true;
        default: return false;
    }
}

const char *DisAssociationDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 2: return opp_typename(typeid(MACAddressExt));
        default: return NULL;
    };
}

void *DisAssociationDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DisAssociation *pp = (DisAssociation *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->getDeviceAddress()); break;
        default: return NULL;
    }
}

Register_Class(Association);

Association::Association(const char *name, int kind) : ::cMessage(name,kind)
{
    this->SecurityLevel_var = 0;
    this->KeyIdMode_var = 0;
    this->KeySource_var = 0;
    this->KeyIndex_var = 0;
}

Association::Association(const Association& other) : ::cMessage(other)
{
    copy(other);
}

Association::~Association()
{
}

Association& Association::operator=(const Association& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void Association::copy(const Association& other)
{
    this->addr_var = other.addr_var;
    this->CapabilityInformation_var = other.CapabilityInformation_var;
    this->SecurityLevel_var = other.SecurityLevel_var;
    this->KeyIdMode_var = other.KeyIdMode_var;
    this->KeySource_var = other.KeySource_var;
    this->KeyIndex_var = other.KeyIndex_var;
}

void Association::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->addr_var);
    doPacking(b,this->CapabilityInformation_var);
    doPacking(b,this->SecurityLevel_var);
    doPacking(b,this->KeyIdMode_var);
    doPacking(b,this->KeySource_var);
    doPacking(b,this->KeyIndex_var);
}

void Association::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->addr_var);
    doUnpacking(b,this->CapabilityInformation_var);
    doUnpacking(b,this->SecurityLevel_var);
    doUnpacking(b,this->KeyIdMode_var);
    doUnpacking(b,this->KeySource_var);
    doUnpacking(b,this->KeyIndex_var);
}

MACAddressExt& Association::getAddr()
{
    return addr_var;
}

void Association::setAddr(const MACAddressExt& addr)
{
    this->addr_var = addr;
}

DevCapability& Association::getCapabilityInformation()
{
    return CapabilityInformation_var;
}

void Association::setCapabilityInformation(const DevCapability& CapabilityInformation)
{
    this->CapabilityInformation_var = CapabilityInformation;
}

unsigned char Association::getSecurityLevel() const
{
    return SecurityLevel_var;
}

void Association::setSecurityLevel(unsigned char SecurityLevel)
{
    this->SecurityLevel_var = SecurityLevel;
}

unsigned char Association::getKeyIdMode() const
{
    return KeyIdMode_var;
}

void Association::setKeyIdMode(unsigned char KeyIdMode)
{
    this->KeyIdMode_var = KeyIdMode;
}

unsigned long Association::getKeySource() const
{
    return KeySource_var;
}

void Association::setKeySource(unsigned long KeySource)
{
    this->KeySource_var = KeySource;
}

unsigned char Association::getKeyIndex() const
{
    return KeyIndex_var;
}

void Association::setKeyIndex(unsigned char KeyIndex)
{
    this->KeyIndex_var = KeyIndex;
}

class AssociationDescriptor : public cClassDescriptor
{
  public:
    AssociationDescriptor();
    virtual ~AssociationDescriptor();

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

Register_ClassDescriptor(AssociationDescriptor);

AssociationDescriptor::AssociationDescriptor() : cClassDescriptor("Association", "cMessage")
{
}

AssociationDescriptor::~AssociationDescriptor()
{
}

bool AssociationDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Association *>(obj)!=NULL;
}

const char *AssociationDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int AssociationDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount(object) : 6;
}

unsigned int AssociationDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *AssociationDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "addr",
        "CapabilityInformation",
        "SecurityLevel",
        "KeyIdMode",
        "KeySource",
        "KeyIndex",
    };
    return (field>=0 && field<6) ? fieldNames[field] : NULL;
}

int AssociationDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='a' && strcmp(fieldName, "addr")==0) return base+0;
    if (fieldName[0]=='C' && strcmp(fieldName, "CapabilityInformation")==0) return base+1;
    if (fieldName[0]=='S' && strcmp(fieldName, "SecurityLevel")==0) return base+2;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeyIdMode")==0) return base+3;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeySource")==0) return base+4;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeyIndex")==0) return base+5;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *AssociationDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "MACAddressExt",
        "DevCapability",
        "unsigned char",
        "unsigned char",
        "unsigned long",
        "unsigned char",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : NULL;
}

const char *AssociationDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int AssociationDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Association *pp = (Association *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string AssociationDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Association *pp = (Association *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getAddr(); return out.str();}
        case 1: {std::stringstream out; out << pp->getCapabilityInformation(); return out.str();}
        case 2: return ulong2string(pp->getSecurityLevel());
        case 3: return ulong2string(pp->getKeyIdMode());
        case 4: return ulong2string(pp->getKeySource());
        case 5: return ulong2string(pp->getKeyIndex());
        default: return "";
    }
}

bool AssociationDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Association *pp = (Association *)object; (void)pp;
    switch (field) {
        case 2: pp->setSecurityLevel(string2ulong(value)); return true;
        case 3: pp->setKeyIdMode(string2ulong(value)); return true;
        case 4: pp->setKeySource(string2ulong(value)); return true;
        case 5: pp->setKeyIndex(string2ulong(value)); return true;
        default: return false;
    }
}

const char *AssociationDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(MACAddressExt));
        case 1: return opp_typename(typeid(DevCapability));
        default: return NULL;
    };
}

void *AssociationDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Association *pp = (Association *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getAddr()); break;
        case 1: return (void *)(&pp->getCapabilityInformation()); break;
        default: return NULL;
    }
}

Register_Class(AssociationRequest);

AssociationRequest::AssociationRequest(const char *name, int kind) : ::Association(name,kind)
{
    this->LogicalChannel_var = 0;
    this->ChannelPage_var = 0;
    this->CoordAddrMode_var = 0;
}

AssociationRequest::AssociationRequest(const AssociationRequest& other) : ::Association(other)
{
    copy(other);
}

AssociationRequest::~AssociationRequest()
{
}

AssociationRequest& AssociationRequest::operator=(const AssociationRequest& other)
{
    if (this==&other) return *this;
    ::Association::operator=(other);
    copy(other);
    return *this;
}

void AssociationRequest::copy(const AssociationRequest& other)
{
    this->LogicalChannel_var = other.LogicalChannel_var;
    this->ChannelPage_var = other.ChannelPage_var;
    this->CoordAddrMode_var = other.CoordAddrMode_var;
    this->CoordPANId_var = other.CoordPANId_var;
    this->CoordAddress_var = other.CoordAddress_var;
}

void AssociationRequest::parsimPack(cCommBuffer *b)
{
    ::Association::parsimPack(b);
    doPacking(b,this->LogicalChannel_var);
    doPacking(b,this->ChannelPage_var);
    doPacking(b,this->CoordAddrMode_var);
    doPacking(b,this->CoordPANId_var);
    doPacking(b,this->CoordAddress_var);
}

void AssociationRequest::parsimUnpack(cCommBuffer *b)
{
    ::Association::parsimUnpack(b);
    doUnpacking(b,this->LogicalChannel_var);
    doUnpacking(b,this->ChannelPage_var);
    doUnpacking(b,this->CoordAddrMode_var);
    doUnpacking(b,this->CoordPANId_var);
    doUnpacking(b,this->CoordAddress_var);
}

unsigned int AssociationRequest::getLogicalChannel() const
{
    return LogicalChannel_var;
}

void AssociationRequest::setLogicalChannel(unsigned int LogicalChannel)
{
    this->LogicalChannel_var = LogicalChannel;
}

unsigned char AssociationRequest::getChannelPage() const
{
    return ChannelPage_var;
}

void AssociationRequest::setChannelPage(unsigned char ChannelPage)
{
    this->ChannelPage_var = ChannelPage;
}

unsigned char AssociationRequest::getCoordAddrMode() const
{
    return CoordAddrMode_var;
}

void AssociationRequest::setCoordAddrMode(unsigned char CoordAddrMode)
{
    this->CoordAddrMode_var = CoordAddrMode;
}

MACAddressExt& AssociationRequest::getCoordPANId()
{
    return CoordPANId_var;
}

void AssociationRequest::setCoordPANId(const MACAddressExt& CoordPANId)
{
    this->CoordPANId_var = CoordPANId;
}

MACAddressExt& AssociationRequest::getCoordAddress()
{
    return CoordAddress_var;
}

void AssociationRequest::setCoordAddress(const MACAddressExt& CoordAddress)
{
    this->CoordAddress_var = CoordAddress;
}

class AssociationRequestDescriptor : public cClassDescriptor
{
  public:
    AssociationRequestDescriptor();
    virtual ~AssociationRequestDescriptor();

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

Register_ClassDescriptor(AssociationRequestDescriptor);

AssociationRequestDescriptor::AssociationRequestDescriptor() : cClassDescriptor("AssociationRequest", "Association")
{
}

AssociationRequestDescriptor::~AssociationRequestDescriptor()
{
}

bool AssociationRequestDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<AssociationRequest *>(obj)!=NULL;
}

const char *AssociationRequestDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int AssociationRequestDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int AssociationRequestDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *AssociationRequestDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "LogicalChannel",
        "ChannelPage",
        "CoordAddrMode",
        "CoordPANId",
        "CoordAddress",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int AssociationRequestDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='L' && strcmp(fieldName, "LogicalChannel")==0) return base+0;
    if (fieldName[0]=='C' && strcmp(fieldName, "ChannelPage")==0) return base+1;
    if (fieldName[0]=='C' && strcmp(fieldName, "CoordAddrMode")==0) return base+2;
    if (fieldName[0]=='C' && strcmp(fieldName, "CoordPANId")==0) return base+3;
    if (fieldName[0]=='C' && strcmp(fieldName, "CoordAddress")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *AssociationRequestDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "unsigned char",
        "unsigned char",
        "MACAddressExt",
        "MACAddressExt",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *AssociationRequestDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 2:
            if (!strcmp(propertyname,"enum")) return "AddrMode";
            return NULL;
        default: return NULL;
    }
}

int AssociationRequestDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    AssociationRequest *pp = (AssociationRequest *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string AssociationRequestDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    AssociationRequest *pp = (AssociationRequest *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getLogicalChannel());
        case 1: return ulong2string(pp->getChannelPage());
        case 2: return ulong2string(pp->getCoordAddrMode());
        case 3: {std::stringstream out; out << pp->getCoordPANId(); return out.str();}
        case 4: {std::stringstream out; out << pp->getCoordAddress(); return out.str();}
        default: return "";
    }
}

bool AssociationRequestDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    AssociationRequest *pp = (AssociationRequest *)object; (void)pp;
    switch (field) {
        case 0: pp->setLogicalChannel(string2ulong(value)); return true;
        case 1: pp->setChannelPage(string2ulong(value)); return true;
        case 2: pp->setCoordAddrMode(string2ulong(value)); return true;
        default: return false;
    }
}

const char *AssociationRequestDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 3: return opp_typename(typeid(MACAddressExt));
        case 4: return opp_typename(typeid(MACAddressExt));
        default: return NULL;
    };
}

void *AssociationRequestDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    AssociationRequest *pp = (AssociationRequest *)object; (void)pp;
    switch (field) {
        case 3: return (void *)(&pp->getCoordPANId()); break;
        case 4: return (void *)(&pp->getCoordAddress()); break;
        default: return NULL;
    }
}

Register_Class(AssociationResponse);

AssociationResponse::AssociationResponse(const char *name, int kind) : ::Association(name,kind)
{
    this->status_var = 0;
}

AssociationResponse::AssociationResponse(const AssociationResponse& other) : ::Association(other)
{
    copy(other);
}

AssociationResponse::~AssociationResponse()
{
}

AssociationResponse& AssociationResponse::operator=(const AssociationResponse& other)
{
    if (this==&other) return *this;
    ::Association::operator=(other);
    copy(other);
    return *this;
}

void AssociationResponse::copy(const AssociationResponse& other)
{
    this->status_var = other.status_var;
}

void AssociationResponse::parsimPack(cCommBuffer *b)
{
    ::Association::parsimPack(b);
    doPacking(b,this->status_var);
}

void AssociationResponse::parsimUnpack(cCommBuffer *b)
{
    ::Association::parsimUnpack(b);
    doUnpacking(b,this->status_var);
}

unsigned short AssociationResponse::getStatus() const
{
    return status_var;
}

void AssociationResponse::setStatus(unsigned short status)
{
    this->status_var = status;
}

class AssociationResponseDescriptor : public cClassDescriptor
{
  public:
    AssociationResponseDescriptor();
    virtual ~AssociationResponseDescriptor();

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

Register_ClassDescriptor(AssociationResponseDescriptor);

AssociationResponseDescriptor::AssociationResponseDescriptor() : cClassDescriptor("AssociationResponse", "Association")
{
}

AssociationResponseDescriptor::~AssociationResponseDescriptor()
{
}

bool AssociationResponseDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<AssociationResponse *>(obj)!=NULL;
}

const char *AssociationResponseDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int AssociationResponseDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int AssociationResponseDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *AssociationResponseDescriptor::getFieldName(void *object, int field) const
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

int AssociationResponseDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *AssociationResponseDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *AssociationResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "MlmeAssociationStatus";
            return NULL;
        default: return NULL;
    }
}

int AssociationResponseDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    AssociationResponse *pp = (AssociationResponse *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string AssociationResponseDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    AssociationResponse *pp = (AssociationResponse *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getStatus());
        default: return "";
    }
}

bool AssociationResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    AssociationResponse *pp = (AssociationResponse *)object; (void)pp;
    switch (field) {
        case 0: pp->setStatus(string2ulong(value)); return true;
        default: return false;
    }
}

const char *AssociationResponseDescriptor::getFieldStructName(void *object, int field) const
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

void *AssociationResponseDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    AssociationResponse *pp = (AssociationResponse *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(AssociationConfirm);

AssociationConfirm::AssociationConfirm(const char *name, int kind) : ::Association(name,kind)
{
    this->status_var = 0;
}

AssociationConfirm::AssociationConfirm(const AssociationConfirm& other) : ::Association(other)
{
    copy(other);
}

AssociationConfirm::~AssociationConfirm()
{
}

AssociationConfirm& AssociationConfirm::operator=(const AssociationConfirm& other)
{
    if (this==&other) return *this;
    ::Association::operator=(other);
    copy(other);
    return *this;
}

void AssociationConfirm::copy(const AssociationConfirm& other)
{
    this->status_var = other.status_var;
}

void AssociationConfirm::parsimPack(cCommBuffer *b)
{
    ::Association::parsimPack(b);
    doPacking(b,this->status_var);
}

void AssociationConfirm::parsimUnpack(cCommBuffer *b)
{
    ::Association::parsimUnpack(b);
    doUnpacking(b,this->status_var);
}

unsigned short AssociationConfirm::getStatus() const
{
    return status_var;
}

void AssociationConfirm::setStatus(unsigned short status)
{
    this->status_var = status;
}

class AssociationConfirmDescriptor : public cClassDescriptor
{
  public:
    AssociationConfirmDescriptor();
    virtual ~AssociationConfirmDescriptor();

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

Register_ClassDescriptor(AssociationConfirmDescriptor);

AssociationConfirmDescriptor::AssociationConfirmDescriptor() : cClassDescriptor("AssociationConfirm", "Association")
{
}

AssociationConfirmDescriptor::~AssociationConfirmDescriptor()
{
}

bool AssociationConfirmDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<AssociationConfirm *>(obj)!=NULL;
}

const char *AssociationConfirmDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int AssociationConfirmDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int AssociationConfirmDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *AssociationConfirmDescriptor::getFieldName(void *object, int field) const
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

int AssociationConfirmDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *AssociationConfirmDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *AssociationConfirmDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "MlmeAssociationStatus";
            return NULL;
        default: return NULL;
    }
}

int AssociationConfirmDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    AssociationConfirm *pp = (AssociationConfirm *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string AssociationConfirmDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    AssociationConfirm *pp = (AssociationConfirm *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getStatus());
        default: return "";
    }
}

bool AssociationConfirmDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    AssociationConfirm *pp = (AssociationConfirm *)object; (void)pp;
    switch (field) {
        case 0: pp->setStatus(string2ulong(value)); return true;
        default: return false;
    }
}

const char *AssociationConfirmDescriptor::getFieldStructName(void *object, int field) const
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

void *AssociationConfirmDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    AssociationConfirm *pp = (AssociationConfirm *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(GTSMessage);

GTSMessage::GTSMessage(const char *name, int kind) : ::cMessage(name,kind)
{
    this->SecurityLevel_var = 0;
    this->KeyIdMode_var = 0;
    this->KeySource_var = 0;
    this->KeyIndex_var = 0;
}

GTSMessage::GTSMessage(const GTSMessage& other) : ::cMessage(other)
{
    copy(other);
}

GTSMessage::~GTSMessage()
{
}

GTSMessage& GTSMessage::operator=(const GTSMessage& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void GTSMessage::copy(const GTSMessage& other)
{
    this->GTSCharacteristics_var = other.GTSCharacteristics_var;
    this->SecurityLevel_var = other.SecurityLevel_var;
    this->KeyIdMode_var = other.KeyIdMode_var;
    this->KeySource_var = other.KeySource_var;
    this->KeyIndex_var = other.KeyIndex_var;
}

void GTSMessage::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->GTSCharacteristics_var);
    doPacking(b,this->SecurityLevel_var);
    doPacking(b,this->KeyIdMode_var);
    doPacking(b,this->KeySource_var);
    doPacking(b,this->KeyIndex_var);
}

void GTSMessage::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->GTSCharacteristics_var);
    doUnpacking(b,this->SecurityLevel_var);
    doUnpacking(b,this->KeyIdMode_var);
    doUnpacking(b,this->KeySource_var);
    doUnpacking(b,this->KeyIndex_var);
}

GTSDescriptor& GTSMessage::getGTSCharacteristics()
{
    return GTSCharacteristics_var;
}

void GTSMessage::setGTSCharacteristics(const GTSDescriptor& GTSCharacteristics)
{
    this->GTSCharacteristics_var = GTSCharacteristics;
}

unsigned char GTSMessage::getSecurityLevel() const
{
    return SecurityLevel_var;
}

void GTSMessage::setSecurityLevel(unsigned char SecurityLevel)
{
    this->SecurityLevel_var = SecurityLevel;
}

unsigned char GTSMessage::getKeyIdMode() const
{
    return KeyIdMode_var;
}

void GTSMessage::setKeyIdMode(unsigned char KeyIdMode)
{
    this->KeyIdMode_var = KeyIdMode;
}

unsigned long GTSMessage::getKeySource() const
{
    return KeySource_var;
}

void GTSMessage::setKeySource(unsigned long KeySource)
{
    this->KeySource_var = KeySource;
}

unsigned char GTSMessage::getKeyIndex() const
{
    return KeyIndex_var;
}

void GTSMessage::setKeyIndex(unsigned char KeyIndex)
{
    this->KeyIndex_var = KeyIndex;
}

class GTSMessageDescriptor : public cClassDescriptor
{
  public:
    GTSMessageDescriptor();
    virtual ~GTSMessageDescriptor();

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

Register_ClassDescriptor(GTSMessageDescriptor);

GTSMessageDescriptor::GTSMessageDescriptor() : cClassDescriptor("GTSMessage", "cMessage")
{
}

GTSMessageDescriptor::~GTSMessageDescriptor()
{
}

bool GTSMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GTSMessage *>(obj)!=NULL;
}

const char *GTSMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GTSMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int GTSMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *GTSMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "GTSCharacteristics",
        "SecurityLevel",
        "KeyIdMode",
        "KeySource",
        "KeyIndex",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int GTSMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='G' && strcmp(fieldName, "GTSCharacteristics")==0) return base+0;
    if (fieldName[0]=='S' && strcmp(fieldName, "SecurityLevel")==0) return base+1;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeyIdMode")==0) return base+2;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeySource")==0) return base+3;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeyIndex")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GTSMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "GTSDescriptor",
        "unsigned char",
        "unsigned char",
        "unsigned long",
        "unsigned char",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *GTSMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int GTSMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GTSMessage *pp = (GTSMessage *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GTSMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GTSMessage *pp = (GTSMessage *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getGTSCharacteristics(); return out.str();}
        case 1: return ulong2string(pp->getSecurityLevel());
        case 2: return ulong2string(pp->getKeyIdMode());
        case 3: return ulong2string(pp->getKeySource());
        case 4: return ulong2string(pp->getKeyIndex());
        default: return "";
    }
}

bool GTSMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GTSMessage *pp = (GTSMessage *)object; (void)pp;
    switch (field) {
        case 1: pp->setSecurityLevel(string2ulong(value)); return true;
        case 2: pp->setKeyIdMode(string2ulong(value)); return true;
        case 3: pp->setKeySource(string2ulong(value)); return true;
        case 4: pp->setKeyIndex(string2ulong(value)); return true;
        default: return false;
    }
}

const char *GTSMessageDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(GTSDescriptor));
        default: return NULL;
    };
}

void *GTSMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GTSMessage *pp = (GTSMessage *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getGTSCharacteristics()); break;
        default: return NULL;
    }
}

Register_Class(GTSIndication);

GTSIndication::GTSIndication(const char *name, int kind) : ::GTSMessage(name,kind)
{
    this->deviceAddr_var = 0;
}

GTSIndication::GTSIndication(const GTSIndication& other) : ::GTSMessage(other)
{
    copy(other);
}

GTSIndication::~GTSIndication()
{
}

GTSIndication& GTSIndication::operator=(const GTSIndication& other)
{
    if (this==&other) return *this;
    ::GTSMessage::operator=(other);
    copy(other);
    return *this;
}

void GTSIndication::copy(const GTSIndication& other)
{
    this->deviceAddr_var = other.deviceAddr_var;
}

void GTSIndication::parsimPack(cCommBuffer *b)
{
    ::GTSMessage::parsimPack(b);
    doPacking(b,this->deviceAddr_var);
}

void GTSIndication::parsimUnpack(cCommBuffer *b)
{
    ::GTSMessage::parsimUnpack(b);
    doUnpacking(b,this->deviceAddr_var);
}

unsigned short GTSIndication::getDeviceAddr() const
{
    return deviceAddr_var;
}

void GTSIndication::setDeviceAddr(unsigned short deviceAddr)
{
    this->deviceAddr_var = deviceAddr;
}

class GTSIndicationDescriptor : public cClassDescriptor
{
  public:
    GTSIndicationDescriptor();
    virtual ~GTSIndicationDescriptor();

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

Register_ClassDescriptor(GTSIndicationDescriptor);

GTSIndicationDescriptor::GTSIndicationDescriptor() : cClassDescriptor("GTSIndication", "GTSMessage")
{
}

GTSIndicationDescriptor::~GTSIndicationDescriptor()
{
}

bool GTSIndicationDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GTSIndication *>(obj)!=NULL;
}

const char *GTSIndicationDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GTSIndicationDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int GTSIndicationDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *GTSIndicationDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "deviceAddr",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int GTSIndicationDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "deviceAddr")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GTSIndicationDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *GTSIndicationDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int GTSIndicationDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GTSIndication *pp = (GTSIndication *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GTSIndicationDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GTSIndication *pp = (GTSIndication *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getDeviceAddr());
        default: return "";
    }
}

bool GTSIndicationDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GTSIndication *pp = (GTSIndication *)object; (void)pp;
    switch (field) {
        case 0: pp->setDeviceAddr(string2ulong(value)); return true;
        default: return false;
    }
}

const char *GTSIndicationDescriptor::getFieldStructName(void *object, int field) const
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

void *GTSIndicationDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GTSIndication *pp = (GTSIndication *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(GTSConfirm);

GTSConfirm::GTSConfirm(const char *name, int kind) : ::cMessage(name,kind)
{
    this->status_var = 0;
}

GTSConfirm::GTSConfirm(const GTSConfirm& other) : ::cMessage(other)
{
    copy(other);
}

GTSConfirm::~GTSConfirm()
{
}

GTSConfirm& GTSConfirm::operator=(const GTSConfirm& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void GTSConfirm::copy(const GTSConfirm& other)
{
    this->gts_var = other.gts_var;
    this->status_var = other.status_var;
}

void GTSConfirm::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->gts_var);
    doPacking(b,this->status_var);
}

void GTSConfirm::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->gts_var);
    doUnpacking(b,this->status_var);
}

GTSDescriptor& GTSConfirm::getGts()
{
    return gts_var;
}

void GTSConfirm::setGts(const GTSDescriptor& gts)
{
    this->gts_var = gts;
}

unsigned short GTSConfirm::getStatus() const
{
    return status_var;
}

void GTSConfirm::setStatus(unsigned short status)
{
    this->status_var = status;
}

class GTSConfirmDescriptor : public cClassDescriptor
{
  public:
    GTSConfirmDescriptor();
    virtual ~GTSConfirmDescriptor();

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

Register_ClassDescriptor(GTSConfirmDescriptor);

GTSConfirmDescriptor::GTSConfirmDescriptor() : cClassDescriptor("GTSConfirm", "cMessage")
{
}

GTSConfirmDescriptor::~GTSConfirmDescriptor()
{
}

bool GTSConfirmDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GTSConfirm *>(obj)!=NULL;
}

const char *GTSConfirmDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GTSConfirmDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int GTSConfirmDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *GTSConfirmDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "gts",
        "status",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int GTSConfirmDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='g' && strcmp(fieldName, "gts")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GTSConfirmDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "GTSDescriptor",
        "unsigned short",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *GTSConfirmDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 1:
            if (!strcmp(propertyname,"enum")) return "MACenum";
            return NULL;
        default: return NULL;
    }
}

int GTSConfirmDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GTSConfirm *pp = (GTSConfirm *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GTSConfirmDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GTSConfirm *pp = (GTSConfirm *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getGts(); return out.str();}
        case 1: return ulong2string(pp->getStatus());
        default: return "";
    }
}

bool GTSConfirmDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GTSConfirm *pp = (GTSConfirm *)object; (void)pp;
    switch (field) {
        case 1: pp->setStatus(string2ulong(value)); return true;
        default: return false;
    }
}

const char *GTSConfirmDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(GTSDescriptor));
        default: return NULL;
    };
}

void *GTSConfirmDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GTSConfirm *pp = (GTSConfirm *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getGts()); break;
        default: return NULL;
    }
}

Register_Class(GetRequest);

GetRequest::GetRequest(const char *name, int kind) : ::cPacket(name,kind)
{
    this->PIBattr_var = 0;
    this->PIBind_var = 0;
}

GetRequest::GetRequest(const GetRequest& other) : ::cPacket(other)
{
    copy(other);
}

GetRequest::~GetRequest()
{
}

GetRequest& GetRequest::operator=(const GetRequest& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void GetRequest::copy(const GetRequest& other)
{
    this->PIBattr_var = other.PIBattr_var;
    this->PIBind_var = other.PIBind_var;
}

void GetRequest::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->PIBattr_var);
    doPacking(b,this->PIBind_var);
}

void GetRequest::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->PIBattr_var);
    doUnpacking(b,this->PIBind_var);
}

unsigned short GetRequest::getPIBattr() const
{
    return PIBattr_var;
}

void GetRequest::setPIBattr(unsigned short PIBattr)
{
    this->PIBattr_var = PIBattr;
}

unsigned short GetRequest::getPIBind() const
{
    return PIBind_var;
}

void GetRequest::setPIBind(unsigned short PIBind)
{
    this->PIBind_var = PIBind;
}

class GetRequestDescriptor : public cClassDescriptor
{
  public:
    GetRequestDescriptor();
    virtual ~GetRequestDescriptor();

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

Register_ClassDescriptor(GetRequestDescriptor);

GetRequestDescriptor::GetRequestDescriptor() : cClassDescriptor("GetRequest", "cPacket")
{
}

GetRequestDescriptor::~GetRequestDescriptor()
{
}

bool GetRequestDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GetRequest *>(obj)!=NULL;
}

const char *GetRequestDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GetRequestDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int GetRequestDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *GetRequestDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "PIBattr",
        "PIBind",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int GetRequestDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='P' && strcmp(fieldName, "PIBattr")==0) return base+0;
    if (fieldName[0]=='P' && strcmp(fieldName, "PIBind")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GetRequestDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
        "unsigned short",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *GetRequestDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "Attributes";
            return NULL;
        default: return NULL;
    }
}

int GetRequestDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GetRequest *pp = (GetRequest *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GetRequestDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GetRequest *pp = (GetRequest *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getPIBattr());
        case 1: return ulong2string(pp->getPIBind());
        default: return "";
    }
}

bool GetRequestDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GetRequest *pp = (GetRequest *)object; (void)pp;
    switch (field) {
        case 0: pp->setPIBattr(string2ulong(value)); return true;
        case 1: pp->setPIBind(string2ulong(value)); return true;
        default: return false;
    }
}

const char *GetRequestDescriptor::getFieldStructName(void *object, int field) const
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

void *GetRequestDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GetRequest *pp = (GetRequest *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(GetConfirm);

GetConfirm::GetConfirm(const char *name, int kind) : ::GetRequest(name,kind)
{
    this->status_var = 0;
    this->value_var = 0;
}

GetConfirm::GetConfirm(const GetConfirm& other) : ::GetRequest(other)
{
    copy(other);
}

GetConfirm::~GetConfirm()
{
}

GetConfirm& GetConfirm::operator=(const GetConfirm& other)
{
    if (this==&other) return *this;
    ::GetRequest::operator=(other);
    copy(other);
    return *this;
}

void GetConfirm::copy(const GetConfirm& other)
{
    this->status_var = other.status_var;
    this->value_var = other.value_var;
}

void GetConfirm::parsimPack(cCommBuffer *b)
{
    ::GetRequest::parsimPack(b);
    doPacking(b,this->status_var);
    doPacking(b,this->value_var);
}

void GetConfirm::parsimUnpack(cCommBuffer *b)
{
    ::GetRequest::parsimUnpack(b);
    doUnpacking(b,this->status_var);
    doUnpacking(b,this->value_var);
}

unsigned short GetConfirm::getStatus() const
{
    return status_var;
}

void GetConfirm::setStatus(unsigned short status)
{
    this->status_var = status;
}

double GetConfirm::getValue() const
{
    return value_var;
}

void GetConfirm::setValue(double value)
{
    this->value_var = value;
}

class GetConfirmDescriptor : public cClassDescriptor
{
  public:
    GetConfirmDescriptor();
    virtual ~GetConfirmDescriptor();

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

Register_ClassDescriptor(GetConfirmDescriptor);

GetConfirmDescriptor::GetConfirmDescriptor() : cClassDescriptor("GetConfirm", "GetRequest")
{
}

GetConfirmDescriptor::~GetConfirmDescriptor()
{
}

bool GetConfirmDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<GetConfirm *>(obj)!=NULL;
}

const char *GetConfirmDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int GetConfirmDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int GetConfirmDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *GetConfirmDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "status",
        "value",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int GetConfirmDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+0;
    if (fieldName[0]=='v' && strcmp(fieldName, "value")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *GetConfirmDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
        "double",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *GetConfirmDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "PhyPIB_Status";
            return NULL;
        default: return NULL;
    }
}

int GetConfirmDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    GetConfirm *pp = (GetConfirm *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string GetConfirmDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    GetConfirm *pp = (GetConfirm *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getStatus());
        case 1: return double2string(pp->getValue());
        default: return "";
    }
}

bool GetConfirmDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    GetConfirm *pp = (GetConfirm *)object; (void)pp;
    switch (field) {
        case 0: pp->setStatus(string2ulong(value)); return true;
        case 1: pp->setValue(string2double(value)); return true;
        default: return false;
    }
}

const char *GetConfirmDescriptor::getFieldStructName(void *object, int field) const
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

void *GetConfirmDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    GetConfirm *pp = (GetConfirm *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(MLMEReset);

MLMEReset::MLMEReset(const char *name, int kind) : ::cMessage(name,kind)
{
    this->setDefaultPIB_var = 0;
}

MLMEReset::MLMEReset(const MLMEReset& other) : ::cMessage(other)
{
    copy(other);
}

MLMEReset::~MLMEReset()
{
}

MLMEReset& MLMEReset::operator=(const MLMEReset& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void MLMEReset::copy(const MLMEReset& other)
{
    this->setDefaultPIB_var = other.setDefaultPIB_var;
}

void MLMEReset::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->setDefaultPIB_var);
}

void MLMEReset::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->setDefaultPIB_var);
}

bool MLMEReset::getSetDefaultPIB() const
{
    return setDefaultPIB_var;
}

void MLMEReset::setSetDefaultPIB(bool setDefaultPIB)
{
    this->setDefaultPIB_var = setDefaultPIB;
}

class MLMEResetDescriptor : public cClassDescriptor
{
  public:
    MLMEResetDescriptor();
    virtual ~MLMEResetDescriptor();

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

Register_ClassDescriptor(MLMEResetDescriptor);

MLMEResetDescriptor::MLMEResetDescriptor() : cClassDescriptor("MLMEReset", "cMessage")
{
}

MLMEResetDescriptor::~MLMEResetDescriptor()
{
}

bool MLMEResetDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<MLMEReset *>(obj)!=NULL;
}

const char *MLMEResetDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int MLMEResetDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int MLMEResetDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *MLMEResetDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "setDefaultPIB",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int MLMEResetDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "setDefaultPIB")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *MLMEResetDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "bool",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *MLMEResetDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int MLMEResetDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    MLMEReset *pp = (MLMEReset *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string MLMEResetDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    MLMEReset *pp = (MLMEReset *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getSetDefaultPIB());
        default: return "";
    }
}

bool MLMEResetDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    MLMEReset *pp = (MLMEReset *)object; (void)pp;
    switch (field) {
        case 0: pp->setSetDefaultPIB(string2bool(value)); return true;
        default: return false;
    }
}

const char *MLMEResetDescriptor::getFieldStructName(void *object, int field) const
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

void *MLMEResetDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    MLMEReset *pp = (MLMEReset *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(RxEnableRequest);

RxEnableRequest::RxEnableRequest(const char *name, int kind) : ::cMessage(name,kind)
{
    this->DeferPermit_var = 0;
    this->RxOnTime_var = 0;
    this->RxOnDuration_var = 0;
}

RxEnableRequest::RxEnableRequest(const RxEnableRequest& other) : ::cMessage(other)
{
    copy(other);
}

RxEnableRequest::~RxEnableRequest()
{
}

RxEnableRequest& RxEnableRequest::operator=(const RxEnableRequest& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void RxEnableRequest::copy(const RxEnableRequest& other)
{
    this->DeferPermit_var = other.DeferPermit_var;
    this->RxOnTime_var = other.RxOnTime_var;
    this->RxOnDuration_var = other.RxOnDuration_var;
}

void RxEnableRequest::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->DeferPermit_var);
    doPacking(b,this->RxOnTime_var);
    doPacking(b,this->RxOnDuration_var);
}

void RxEnableRequest::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->DeferPermit_var);
    doUnpacking(b,this->RxOnTime_var);
    doUnpacking(b,this->RxOnDuration_var);
}

bool RxEnableRequest::getDeferPermit() const
{
    return DeferPermit_var;
}

void RxEnableRequest::setDeferPermit(bool DeferPermit)
{
    this->DeferPermit_var = DeferPermit;
}

simtime_t RxEnableRequest::getRxOnTime() const
{
    return RxOnTime_var;
}

void RxEnableRequest::setRxOnTime(simtime_t RxOnTime)
{
    this->RxOnTime_var = RxOnTime;
}

unsigned int RxEnableRequest::getRxOnDuration() const
{
    return RxOnDuration_var;
}

void RxEnableRequest::setRxOnDuration(unsigned int RxOnDuration)
{
    this->RxOnDuration_var = RxOnDuration;
}

class RxEnableRequestDescriptor : public cClassDescriptor
{
  public:
    RxEnableRequestDescriptor();
    virtual ~RxEnableRequestDescriptor();

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

Register_ClassDescriptor(RxEnableRequestDescriptor);

RxEnableRequestDescriptor::RxEnableRequestDescriptor() : cClassDescriptor("RxEnableRequest", "cMessage")
{
}

RxEnableRequestDescriptor::~RxEnableRequestDescriptor()
{
}

bool RxEnableRequestDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<RxEnableRequest *>(obj)!=NULL;
}

const char *RxEnableRequestDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int RxEnableRequestDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int RxEnableRequestDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *RxEnableRequestDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "DeferPermit",
        "RxOnTime",
        "RxOnDuration",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int RxEnableRequestDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='D' && strcmp(fieldName, "DeferPermit")==0) return base+0;
    if (fieldName[0]=='R' && strcmp(fieldName, "RxOnTime")==0) return base+1;
    if (fieldName[0]=='R' && strcmp(fieldName, "RxOnDuration")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *RxEnableRequestDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "simtime_t",
        "unsigned int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *RxEnableRequestDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int RxEnableRequestDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    RxEnableRequest *pp = (RxEnableRequest *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string RxEnableRequestDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    RxEnableRequest *pp = (RxEnableRequest *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getDeferPermit());
        case 1: return double2string(pp->getRxOnTime());
        case 2: return ulong2string(pp->getRxOnDuration());
        default: return "";
    }
}

bool RxEnableRequestDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    RxEnableRequest *pp = (RxEnableRequest *)object; (void)pp;
    switch (field) {
        case 0: pp->setDeferPermit(string2bool(value)); return true;
        case 1: pp->setRxOnTime(string2double(value)); return true;
        case 2: pp->setRxOnDuration(string2ulong(value)); return true;
        default: return false;
    }
}

const char *RxEnableRequestDescriptor::getFieldStructName(void *object, int field) const
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

void *RxEnableRequestDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    RxEnableRequest *pp = (RxEnableRequest *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(RxEnableConfirm);

RxEnableConfirm::RxEnableConfirm(const char *name, int kind) : ::cMessage(name,kind)
{
    this->status_var = 0;
}

RxEnableConfirm::RxEnableConfirm(const RxEnableConfirm& other) : ::cMessage(other)
{
    copy(other);
}

RxEnableConfirm::~RxEnableConfirm()
{
}

RxEnableConfirm& RxEnableConfirm::operator=(const RxEnableConfirm& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void RxEnableConfirm::copy(const RxEnableConfirm& other)
{
    this->status_var = other.status_var;
}

void RxEnableConfirm::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->status_var);
}

void RxEnableConfirm::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->status_var);
}

int RxEnableConfirm::getStatus() const
{
    return status_var;
}

void RxEnableConfirm::setStatus(int status)
{
    this->status_var = status;
}

class RxEnableConfirmDescriptor : public cClassDescriptor
{
  public:
    RxEnableConfirmDescriptor();
    virtual ~RxEnableConfirmDescriptor();

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

Register_ClassDescriptor(RxEnableConfirmDescriptor);

RxEnableConfirmDescriptor::RxEnableConfirmDescriptor() : cClassDescriptor("RxEnableConfirm", "cMessage")
{
}

RxEnableConfirmDescriptor::~RxEnableConfirmDescriptor()
{
}

bool RxEnableConfirmDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<RxEnableConfirm *>(obj)!=NULL;
}

const char *RxEnableConfirmDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int RxEnableConfirmDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int RxEnableConfirmDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *RxEnableConfirmDescriptor::getFieldName(void *object, int field) const
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

int RxEnableConfirmDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *RxEnableConfirmDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *RxEnableConfirmDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "RxEnableStatus";
            return NULL;
        default: return NULL;
    }
}

int RxEnableConfirmDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    RxEnableConfirm *pp = (RxEnableConfirm *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string RxEnableConfirmDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    RxEnableConfirm *pp = (RxEnableConfirm *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getStatus());
        default: return "";
    }
}

bool RxEnableConfirmDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    RxEnableConfirm *pp = (RxEnableConfirm *)object; (void)pp;
    switch (field) {
        case 0: pp->setStatus(string2long(value)); return true;
        default: return false;
    }
}

const char *RxEnableConfirmDescriptor::getFieldStructName(void *object, int field) const
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

void *RxEnableConfirmDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    RxEnableConfirm *pp = (RxEnableConfirm *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(ScanRequest);

ScanRequest::ScanRequest(const char *name, int kind) : ::cMessage(name,kind)
{
    this->ScanType_var = 0;
    this->ScanChannels_var = 0;
    this->ScanDuration_var = 0;
    this->ChannelPage_var = 0;
    this->SecurityLevel_var = 0;
    this->KeyIdMode_var = 0;
    this->KeySource_var = 0;
    this->KeyIndex_var = 0;
}

ScanRequest::ScanRequest(const ScanRequest& other) : ::cMessage(other)
{
    copy(other);
}

ScanRequest::~ScanRequest()
{
}

ScanRequest& ScanRequest::operator=(const ScanRequest& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void ScanRequest::copy(const ScanRequest& other)
{
    this->ScanType_var = other.ScanType_var;
    this->ScanChannels_var = other.ScanChannels_var;
    this->ScanDuration_var = other.ScanDuration_var;
    this->ChannelPage_var = other.ChannelPage_var;
    this->SecurityLevel_var = other.SecurityLevel_var;
    this->KeyIdMode_var = other.KeyIdMode_var;
    this->KeySource_var = other.KeySource_var;
    this->KeyIndex_var = other.KeyIndex_var;
}

void ScanRequest::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->ScanType_var);
    doPacking(b,this->ScanChannels_var);
    doPacking(b,this->ScanDuration_var);
    doPacking(b,this->ChannelPage_var);
    doPacking(b,this->SecurityLevel_var);
    doPacking(b,this->KeyIdMode_var);
    doPacking(b,this->KeySource_var);
    doPacking(b,this->KeyIndex_var);
}

void ScanRequest::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->ScanType_var);
    doUnpacking(b,this->ScanChannels_var);
    doUnpacking(b,this->ScanDuration_var);
    doUnpacking(b,this->ChannelPage_var);
    doUnpacking(b,this->SecurityLevel_var);
    doUnpacking(b,this->KeyIdMode_var);
    doUnpacking(b,this->KeySource_var);
    doUnpacking(b,this->KeyIndex_var);
}

unsigned char ScanRequest::getScanType() const
{
    return ScanType_var;
}

void ScanRequest::setScanType(unsigned char ScanType)
{
    this->ScanType_var = ScanType;
}

unsigned int ScanRequest::getScanChannels() const
{
    return ScanChannels_var;
}

void ScanRequest::setScanChannels(unsigned int ScanChannels)
{
    this->ScanChannels_var = ScanChannels;
}

unsigned int ScanRequest::getScanDuration() const
{
    return ScanDuration_var;
}

void ScanRequest::setScanDuration(unsigned int ScanDuration)
{
    this->ScanDuration_var = ScanDuration;
}

unsigned char ScanRequest::getChannelPage() const
{
    return ChannelPage_var;
}

void ScanRequest::setChannelPage(unsigned char ChannelPage)
{
    this->ChannelPage_var = ChannelPage;
}

unsigned char ScanRequest::getSecurityLevel() const
{
    return SecurityLevel_var;
}

void ScanRequest::setSecurityLevel(unsigned char SecurityLevel)
{
    this->SecurityLevel_var = SecurityLevel;
}

unsigned char ScanRequest::getKeyIdMode() const
{
    return KeyIdMode_var;
}

void ScanRequest::setKeyIdMode(unsigned char KeyIdMode)
{
    this->KeyIdMode_var = KeyIdMode;
}

unsigned long ScanRequest::getKeySource() const
{
    return KeySource_var;
}

void ScanRequest::setKeySource(unsigned long KeySource)
{
    this->KeySource_var = KeySource;
}

unsigned char ScanRequest::getKeyIndex() const
{
    return KeyIndex_var;
}

void ScanRequest::setKeyIndex(unsigned char KeyIndex)
{
    this->KeyIndex_var = KeyIndex;
}

class ScanRequestDescriptor : public cClassDescriptor
{
  public:
    ScanRequestDescriptor();
    virtual ~ScanRequestDescriptor();

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

Register_ClassDescriptor(ScanRequestDescriptor);

ScanRequestDescriptor::ScanRequestDescriptor() : cClassDescriptor("ScanRequest", "cMessage")
{
}

ScanRequestDescriptor::~ScanRequestDescriptor()
{
}

bool ScanRequestDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ScanRequest *>(obj)!=NULL;
}

const char *ScanRequestDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ScanRequestDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
}

unsigned int ScanRequestDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *ScanRequestDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "ScanType",
        "ScanChannels",
        "ScanDuration",
        "ChannelPage",
        "SecurityLevel",
        "KeyIdMode",
        "KeySource",
        "KeyIndex",
    };
    return (field>=0 && field<8) ? fieldNames[field] : NULL;
}

int ScanRequestDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='S' && strcmp(fieldName, "ScanType")==0) return base+0;
    if (fieldName[0]=='S' && strcmp(fieldName, "ScanChannels")==0) return base+1;
    if (fieldName[0]=='S' && strcmp(fieldName, "ScanDuration")==0) return base+2;
    if (fieldName[0]=='C' && strcmp(fieldName, "ChannelPage")==0) return base+3;
    if (fieldName[0]=='S' && strcmp(fieldName, "SecurityLevel")==0) return base+4;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeyIdMode")==0) return base+5;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeySource")==0) return base+6;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeyIndex")==0) return base+7;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ScanRequestDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "unsigned int",
        "unsigned int",
        "unsigned char",
        "unsigned char",
        "unsigned char",
        "unsigned long",
        "unsigned char",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : NULL;
}

const char *ScanRequestDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "ScanType";
            return NULL;
        default: return NULL;
    }
}

int ScanRequestDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ScanRequest *pp = (ScanRequest *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ScanRequestDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ScanRequest *pp = (ScanRequest *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getScanType());
        case 1: return ulong2string(pp->getScanChannels());
        case 2: return ulong2string(pp->getScanDuration());
        case 3: return ulong2string(pp->getChannelPage());
        case 4: return ulong2string(pp->getSecurityLevel());
        case 5: return ulong2string(pp->getKeyIdMode());
        case 6: return ulong2string(pp->getKeySource());
        case 7: return ulong2string(pp->getKeyIndex());
        default: return "";
    }
}

bool ScanRequestDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ScanRequest *pp = (ScanRequest *)object; (void)pp;
    switch (field) {
        case 0: pp->setScanType(string2ulong(value)); return true;
        case 1: pp->setScanChannels(string2ulong(value)); return true;
        case 2: pp->setScanDuration(string2ulong(value)); return true;
        case 3: pp->setChannelPage(string2ulong(value)); return true;
        case 4: pp->setSecurityLevel(string2ulong(value)); return true;
        case 5: pp->setKeyIdMode(string2ulong(value)); return true;
        case 6: pp->setKeySource(string2ulong(value)); return true;
        case 7: pp->setKeyIndex(string2ulong(value)); return true;
        default: return false;
    }
}

const char *ScanRequestDescriptor::getFieldStructName(void *object, int field) const
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

void *ScanRequestDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ScanRequest *pp = (ScanRequest *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(ScanConfirm);

ScanConfirm::ScanConfirm(const char *name, int kind) : ::cMessage(name,kind)
{
    this->status_var = 0;
    this->ScanType_var = 0;
    this->ChannelPage_var = 0;
    this->UnscannedChannels_var = 0;
    this->ResultListSize_var = 0;
    EnergyDetectList_arraysize = 0;
    this->EnergyDetectList_var = 0;
    PANDescriptorList_arraysize = 0;
    this->PANDescriptorList_var = 0;
}

ScanConfirm::ScanConfirm(const ScanConfirm& other) : ::cMessage(other)
{
    EnergyDetectList_arraysize = 0;
    this->EnergyDetectList_var = 0;
    PANDescriptorList_arraysize = 0;
    this->PANDescriptorList_var = 0;
    copy(other);
}

ScanConfirm::~ScanConfirm()
{
    delete [] EnergyDetectList_var;
    delete [] PANDescriptorList_var;
}

ScanConfirm& ScanConfirm::operator=(const ScanConfirm& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void ScanConfirm::copy(const ScanConfirm& other)
{
    this->status_var = other.status_var;
    this->ScanType_var = other.ScanType_var;
    this->ChannelPage_var = other.ChannelPage_var;
    this->UnscannedChannels_var = other.UnscannedChannels_var;
    this->ResultListSize_var = other.ResultListSize_var;
    delete [] this->EnergyDetectList_var;
    this->EnergyDetectList_var = (other.EnergyDetectList_arraysize==0) ? NULL : new unsigned char[other.EnergyDetectList_arraysize];
    EnergyDetectList_arraysize = other.EnergyDetectList_arraysize;
    for (unsigned int i=0; i<EnergyDetectList_arraysize; i++)
        this->EnergyDetectList_var[i] = other.EnergyDetectList_var[i];
    delete [] this->PANDescriptorList_var;
    this->PANDescriptorList_var = (other.PANDescriptorList_arraysize==0) ? NULL : new PAN_ELE[other.PANDescriptorList_arraysize];
    PANDescriptorList_arraysize = other.PANDescriptorList_arraysize;
    for (unsigned int i=0; i<PANDescriptorList_arraysize; i++)
        this->PANDescriptorList_var[i] = other.PANDescriptorList_var[i];
}

void ScanConfirm::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->status_var);
    doPacking(b,this->ScanType_var);
    doPacking(b,this->ChannelPage_var);
    doPacking(b,this->UnscannedChannels_var);
    doPacking(b,this->ResultListSize_var);
    b->pack(EnergyDetectList_arraysize);
    doPacking(b,this->EnergyDetectList_var,EnergyDetectList_arraysize);
    b->pack(PANDescriptorList_arraysize);
    doPacking(b,this->PANDescriptorList_var,PANDescriptorList_arraysize);
}

void ScanConfirm::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->status_var);
    doUnpacking(b,this->ScanType_var);
    doUnpacking(b,this->ChannelPage_var);
    doUnpacking(b,this->UnscannedChannels_var);
    doUnpacking(b,this->ResultListSize_var);
    delete [] this->EnergyDetectList_var;
    b->unpack(EnergyDetectList_arraysize);
    if (EnergyDetectList_arraysize==0) {
        this->EnergyDetectList_var = 0;
    } else {
        this->EnergyDetectList_var = new unsigned char[EnergyDetectList_arraysize];
        doUnpacking(b,this->EnergyDetectList_var,EnergyDetectList_arraysize);
    }
    delete [] this->PANDescriptorList_var;
    b->unpack(PANDescriptorList_arraysize);
    if (PANDescriptorList_arraysize==0) {
        this->PANDescriptorList_var = 0;
    } else {
        this->PANDescriptorList_var = new PAN_ELE[PANDescriptorList_arraysize];
        doUnpacking(b,this->PANDescriptorList_var,PANDescriptorList_arraysize);
    }
}

unsigned char ScanConfirm::getStatus() const
{
    return status_var;
}

void ScanConfirm::setStatus(unsigned char status)
{
    this->status_var = status;
}

unsigned char ScanConfirm::getScanType() const
{
    return ScanType_var;
}

void ScanConfirm::setScanType(unsigned char ScanType)
{
    this->ScanType_var = ScanType;
}

unsigned char ScanConfirm::getChannelPage() const
{
    return ChannelPage_var;
}

void ScanConfirm::setChannelPage(unsigned char ChannelPage)
{
    this->ChannelPage_var = ChannelPage;
}

unsigned int ScanConfirm::getUnscannedChannels() const
{
    return UnscannedChannels_var;
}

void ScanConfirm::setUnscannedChannels(unsigned int UnscannedChannels)
{
    this->UnscannedChannels_var = UnscannedChannels;
}

unsigned short ScanConfirm::getResultListSize() const
{
    return ResultListSize_var;
}

void ScanConfirm::setResultListSize(unsigned short ResultListSize)
{
    this->ResultListSize_var = ResultListSize;
}

void ScanConfirm::setEnergyDetectListArraySize(unsigned int size)
{
    unsigned char *EnergyDetectList_var2 = (size==0) ? NULL : new unsigned char[size];
    unsigned int sz = EnergyDetectList_arraysize < size ? EnergyDetectList_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        EnergyDetectList_var2[i] = this->EnergyDetectList_var[i];
    for (unsigned int i=sz; i<size; i++)
        EnergyDetectList_var2[i] = 0;
    EnergyDetectList_arraysize = size;
    delete [] this->EnergyDetectList_var;
    this->EnergyDetectList_var = EnergyDetectList_var2;
}

unsigned int ScanConfirm::getEnergyDetectListArraySize() const
{
    return EnergyDetectList_arraysize;
}

unsigned char ScanConfirm::getEnergyDetectList(unsigned int k) const
{
    if (k>=EnergyDetectList_arraysize) throw cRuntimeError("Array of size %d indexed by %d", EnergyDetectList_arraysize, k);
    return EnergyDetectList_var[k];
}

void ScanConfirm::setEnergyDetectList(unsigned int k, unsigned char EnergyDetectList)
{
    if (k>=EnergyDetectList_arraysize) throw cRuntimeError("Array of size %d indexed by %d", EnergyDetectList_arraysize, k);
    this->EnergyDetectList_var[k] = EnergyDetectList;
}

void ScanConfirm::setPANDescriptorListArraySize(unsigned int size)
{
    PAN_ELE *PANDescriptorList_var2 = (size==0) ? NULL : new PAN_ELE[size];
    unsigned int sz = PANDescriptorList_arraysize < size ? PANDescriptorList_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        PANDescriptorList_var2[i] = this->PANDescriptorList_var[i];
    PANDescriptorList_arraysize = size;
    delete [] this->PANDescriptorList_var;
    this->PANDescriptorList_var = PANDescriptorList_var2;
}

unsigned int ScanConfirm::getPANDescriptorListArraySize() const
{
    return PANDescriptorList_arraysize;
}

PAN_ELE& ScanConfirm::getPANDescriptorList(unsigned int k)
{
    if (k>=PANDescriptorList_arraysize) throw cRuntimeError("Array of size %d indexed by %d", PANDescriptorList_arraysize, k);
    return PANDescriptorList_var[k];
}

void ScanConfirm::setPANDescriptorList(unsigned int k, const PAN_ELE& PANDescriptorList)
{
    if (k>=PANDescriptorList_arraysize) throw cRuntimeError("Array of size %d indexed by %d", PANDescriptorList_arraysize, k);
    this->PANDescriptorList_var[k] = PANDescriptorList;
}

class ScanConfirmDescriptor : public cClassDescriptor
{
  public:
    ScanConfirmDescriptor();
    virtual ~ScanConfirmDescriptor();

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

Register_ClassDescriptor(ScanConfirmDescriptor);

ScanConfirmDescriptor::ScanConfirmDescriptor() : cClassDescriptor("ScanConfirm", "cMessage")
{
}

ScanConfirmDescriptor::~ScanConfirmDescriptor()
{
}

bool ScanConfirmDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ScanConfirm *>(obj)!=NULL;
}

const char *ScanConfirmDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ScanConfirmDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int ScanConfirmDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *ScanConfirmDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "status",
        "ScanType",
        "ChannelPage",
        "UnscannedChannels",
        "ResultListSize",
        "EnergyDetectList",
        "PANDescriptorList",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int ScanConfirmDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+0;
    if (fieldName[0]=='S' && strcmp(fieldName, "ScanType")==0) return base+1;
    if (fieldName[0]=='C' && strcmp(fieldName, "ChannelPage")==0) return base+2;
    if (fieldName[0]=='U' && strcmp(fieldName, "UnscannedChannels")==0) return base+3;
    if (fieldName[0]=='R' && strcmp(fieldName, "ResultListSize")==0) return base+4;
    if (fieldName[0]=='E' && strcmp(fieldName, "EnergyDetectList")==0) return base+5;
    if (fieldName[0]=='P' && strcmp(fieldName, "PANDescriptorList")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ScanConfirmDescriptor::getFieldTypeString(void *object, int field) const
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
        "unsigned int",
        "unsigned short",
        "unsigned char",
        "PAN_ELE",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *ScanConfirmDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "ScanStatus";
            return NULL;
        case 1:
            if (!strcmp(propertyname,"enum")) return "ScanType";
            return NULL;
        default: return NULL;
    }
}

int ScanConfirmDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ScanConfirm *pp = (ScanConfirm *)object; (void)pp;
    switch (field) {
        case 5: return pp->getEnergyDetectListArraySize();
        case 6: return pp->getPANDescriptorListArraySize();
        default: return 0;
    }
}

std::string ScanConfirmDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ScanConfirm *pp = (ScanConfirm *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getStatus());
        case 1: return ulong2string(pp->getScanType());
        case 2: return ulong2string(pp->getChannelPage());
        case 3: return ulong2string(pp->getUnscannedChannels());
        case 4: return ulong2string(pp->getResultListSize());
        case 5: return ulong2string(pp->getEnergyDetectList(i));
        case 6: {std::stringstream out; out << pp->getPANDescriptorList(i); return out.str();}
        default: return "";
    }
}

bool ScanConfirmDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ScanConfirm *pp = (ScanConfirm *)object; (void)pp;
    switch (field) {
        case 0: pp->setStatus(string2ulong(value)); return true;
        case 1: pp->setScanType(string2ulong(value)); return true;
        case 2: pp->setChannelPage(string2ulong(value)); return true;
        case 3: pp->setUnscannedChannels(string2ulong(value)); return true;
        case 4: pp->setResultListSize(string2ulong(value)); return true;
        case 5: pp->setEnergyDetectList(i,string2ulong(value)); return true;
        default: return false;
    }
}

const char *ScanConfirmDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 6: return opp_typename(typeid(PAN_ELE));
        default: return NULL;
    };
}

void *ScanConfirmDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ScanConfirm *pp = (ScanConfirm *)object; (void)pp;
    switch (field) {
        case 6: return (void *)(&pp->getPANDescriptorList(i)); break;
        default: return NULL;
    }
}

Register_Class(OrphanIndication);

OrphanIndication::OrphanIndication(const char *name, int kind) : ::cPacket(name,kind)
{
    this->SecurityLevel_var = 0;
    this->KeyIdMode_var = 0;
    this->KeySource_var = 0;
    this->KeyIndex_var = 0;
}

OrphanIndication::OrphanIndication(const OrphanIndication& other) : ::cPacket(other)
{
    copy(other);
}

OrphanIndication::~OrphanIndication()
{
}

OrphanIndication& OrphanIndication::operator=(const OrphanIndication& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void OrphanIndication::copy(const OrphanIndication& other)
{
    this->OrphanAddress_var = other.OrphanAddress_var;
    this->SecurityLevel_var = other.SecurityLevel_var;
    this->KeyIdMode_var = other.KeyIdMode_var;
    this->KeySource_var = other.KeySource_var;
    this->KeyIndex_var = other.KeyIndex_var;
}

void OrphanIndication::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->OrphanAddress_var);
    doPacking(b,this->SecurityLevel_var);
    doPacking(b,this->KeyIdMode_var);
    doPacking(b,this->KeySource_var);
    doPacking(b,this->KeyIndex_var);
}

void OrphanIndication::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->OrphanAddress_var);
    doUnpacking(b,this->SecurityLevel_var);
    doUnpacking(b,this->KeyIdMode_var);
    doUnpacking(b,this->KeySource_var);
    doUnpacking(b,this->KeyIndex_var);
}

MACAddressExt& OrphanIndication::getOrphanAddress()
{
    return OrphanAddress_var;
}

void OrphanIndication::setOrphanAddress(const MACAddressExt& OrphanAddress)
{
    this->OrphanAddress_var = OrphanAddress;
}

unsigned char OrphanIndication::getSecurityLevel() const
{
    return SecurityLevel_var;
}

void OrphanIndication::setSecurityLevel(unsigned char SecurityLevel)
{
    this->SecurityLevel_var = SecurityLevel;
}

unsigned char OrphanIndication::getKeyIdMode() const
{
    return KeyIdMode_var;
}

void OrphanIndication::setKeyIdMode(unsigned char KeyIdMode)
{
    this->KeyIdMode_var = KeyIdMode;
}

unsigned long OrphanIndication::getKeySource() const
{
    return KeySource_var;
}

void OrphanIndication::setKeySource(unsigned long KeySource)
{
    this->KeySource_var = KeySource;
}

unsigned char OrphanIndication::getKeyIndex() const
{
    return KeyIndex_var;
}

void OrphanIndication::setKeyIndex(unsigned char KeyIndex)
{
    this->KeyIndex_var = KeyIndex;
}

class OrphanIndicationDescriptor : public cClassDescriptor
{
  public:
    OrphanIndicationDescriptor();
    virtual ~OrphanIndicationDescriptor();

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

Register_ClassDescriptor(OrphanIndicationDescriptor);

OrphanIndicationDescriptor::OrphanIndicationDescriptor() : cClassDescriptor("OrphanIndication", "cPacket")
{
}

OrphanIndicationDescriptor::~OrphanIndicationDescriptor()
{
}

bool OrphanIndicationDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OrphanIndication *>(obj)!=NULL;
}

const char *OrphanIndicationDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OrphanIndicationDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int OrphanIndicationDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *OrphanIndicationDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "OrphanAddress",
        "SecurityLevel",
        "KeyIdMode",
        "KeySource",
        "KeyIndex",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int OrphanIndicationDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='O' && strcmp(fieldName, "OrphanAddress")==0) return base+0;
    if (fieldName[0]=='S' && strcmp(fieldName, "SecurityLevel")==0) return base+1;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeyIdMode")==0) return base+2;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeySource")==0) return base+3;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeyIndex")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OrphanIndicationDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "MACAddressExt",
        "unsigned char",
        "unsigned char",
        "unsigned long",
        "unsigned char",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *OrphanIndicationDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int OrphanIndicationDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OrphanIndication *pp = (OrphanIndication *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string OrphanIndicationDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OrphanIndication *pp = (OrphanIndication *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getOrphanAddress(); return out.str();}
        case 1: return ulong2string(pp->getSecurityLevel());
        case 2: return ulong2string(pp->getKeyIdMode());
        case 3: return ulong2string(pp->getKeySource());
        case 4: return ulong2string(pp->getKeyIndex());
        default: return "";
    }
}

bool OrphanIndicationDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OrphanIndication *pp = (OrphanIndication *)object; (void)pp;
    switch (field) {
        case 1: pp->setSecurityLevel(string2ulong(value)); return true;
        case 2: pp->setKeyIdMode(string2ulong(value)); return true;
        case 3: pp->setKeySource(string2ulong(value)); return true;
        case 4: pp->setKeyIndex(string2ulong(value)); return true;
        default: return false;
    }
}

const char *OrphanIndicationDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(MACAddressExt));
        default: return NULL;
    };
}

void *OrphanIndicationDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OrphanIndication *pp = (OrphanIndication *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getOrphanAddress()); break;
        default: return NULL;
    }
}

Register_Class(OrphanResponse);

OrphanResponse::OrphanResponse(const char *name, int kind) : ::OrphanIndication(name,kind)
{
    this->ShortAddress_var = 0;
    this->AssociatedMember_var = 0;
}

OrphanResponse::OrphanResponse(const OrphanResponse& other) : ::OrphanIndication(other)
{
    copy(other);
}

OrphanResponse::~OrphanResponse()
{
}

OrphanResponse& OrphanResponse::operator=(const OrphanResponse& other)
{
    if (this==&other) return *this;
    ::OrphanIndication::operator=(other);
    copy(other);
    return *this;
}

void OrphanResponse::copy(const OrphanResponse& other)
{
    this->ShortAddress_var = other.ShortAddress_var;
    this->AssociatedMember_var = other.AssociatedMember_var;
}

void OrphanResponse::parsimPack(cCommBuffer *b)
{
    ::OrphanIndication::parsimPack(b);
    doPacking(b,this->ShortAddress_var);
    doPacking(b,this->AssociatedMember_var);
}

void OrphanResponse::parsimUnpack(cCommBuffer *b)
{
    ::OrphanIndication::parsimUnpack(b);
    doUnpacking(b,this->ShortAddress_var);
    doUnpacking(b,this->AssociatedMember_var);
}

unsigned short OrphanResponse::getShortAddress() const
{
    return ShortAddress_var;
}

void OrphanResponse::setShortAddress(unsigned short ShortAddress)
{
    this->ShortAddress_var = ShortAddress;
}

bool OrphanResponse::getAssociatedMember() const
{
    return AssociatedMember_var;
}

void OrphanResponse::setAssociatedMember(bool AssociatedMember)
{
    this->AssociatedMember_var = AssociatedMember;
}

class OrphanResponseDescriptor : public cClassDescriptor
{
  public:
    OrphanResponseDescriptor();
    virtual ~OrphanResponseDescriptor();

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

Register_ClassDescriptor(OrphanResponseDescriptor);

OrphanResponseDescriptor::OrphanResponseDescriptor() : cClassDescriptor("OrphanResponse", "OrphanIndication")
{
}

OrphanResponseDescriptor::~OrphanResponseDescriptor()
{
}

bool OrphanResponseDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OrphanResponse *>(obj)!=NULL;
}

const char *OrphanResponseDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OrphanResponseDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int OrphanResponseDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *OrphanResponseDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "ShortAddress",
        "AssociatedMember",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int OrphanResponseDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='S' && strcmp(fieldName, "ShortAddress")==0) return base+0;
    if (fieldName[0]=='A' && strcmp(fieldName, "AssociatedMember")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OrphanResponseDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
        "bool",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *OrphanResponseDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int OrphanResponseDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OrphanResponse *pp = (OrphanResponse *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string OrphanResponseDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OrphanResponse *pp = (OrphanResponse *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getShortAddress());
        case 1: return bool2string(pp->getAssociatedMember());
        default: return "";
    }
}

bool OrphanResponseDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OrphanResponse *pp = (OrphanResponse *)object; (void)pp;
    switch (field) {
        case 0: pp->setShortAddress(string2ulong(value)); return true;
        case 1: pp->setAssociatedMember(string2bool(value)); return true;
        default: return false;
    }
}

const char *OrphanResponseDescriptor::getFieldStructName(void *object, int field) const
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

void *OrphanResponseDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OrphanResponse *pp = (OrphanResponse *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(StartRequest);

StartRequest::StartRequest(const char *name, int kind) : ::cMessage(name,kind)
{
    this->PANId_var = 0;
    this->LogicalChannel_var = 0;
    this->ChannelPage_var = 0;
    this->StartTime_var = 0;
    this->BeaconOrder_var = 0;
    this->SuperframeOrder_var = 0;
    this->PANCoordinator_var = 0;
    this->BatteryLifeExtension_var = 0;
    this->CoordRealignment_var = 0;
    this->CoordRealignSecurityLevel_var = 0;
    this->CoordRealignKeyIdMode_var = 0;
    this->CoordRealignKeySource_var = 0;
    this->CoordRealignKeyIndex_var = 0;
    this->BeaconSecurityLevel_var = 0;
    this->BeaconKeyIdMode_var = 0;
    this->BeaconKeySource_var = 0;
    this->BeaconKeyIndex_var = 0;
}

StartRequest::StartRequest(const StartRequest& other) : ::cMessage(other)
{
    copy(other);
}

StartRequest::~StartRequest()
{
}

StartRequest& StartRequest::operator=(const StartRequest& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void StartRequest::copy(const StartRequest& other)
{
    this->PANId_var = other.PANId_var;
    this->LogicalChannel_var = other.LogicalChannel_var;
    this->ChannelPage_var = other.ChannelPage_var;
    this->StartTime_var = other.StartTime_var;
    this->BeaconOrder_var = other.BeaconOrder_var;
    this->SuperframeOrder_var = other.SuperframeOrder_var;
    this->PANCoordinator_var = other.PANCoordinator_var;
    this->BatteryLifeExtension_var = other.BatteryLifeExtension_var;
    this->CoordRealignment_var = other.CoordRealignment_var;
    this->CoordRealignSecurityLevel_var = other.CoordRealignSecurityLevel_var;
    this->CoordRealignKeyIdMode_var = other.CoordRealignKeyIdMode_var;
    this->CoordRealignKeySource_var = other.CoordRealignKeySource_var;
    this->CoordRealignKeyIndex_var = other.CoordRealignKeyIndex_var;
    this->BeaconSecurityLevel_var = other.BeaconSecurityLevel_var;
    this->BeaconKeyIdMode_var = other.BeaconKeyIdMode_var;
    this->BeaconKeySource_var = other.BeaconKeySource_var;
    this->BeaconKeyIndex_var = other.BeaconKeyIndex_var;
}

void StartRequest::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->PANId_var);
    doPacking(b,this->LogicalChannel_var);
    doPacking(b,this->ChannelPage_var);
    doPacking(b,this->StartTime_var);
    doPacking(b,this->BeaconOrder_var);
    doPacking(b,this->SuperframeOrder_var);
    doPacking(b,this->PANCoordinator_var);
    doPacking(b,this->BatteryLifeExtension_var);
    doPacking(b,this->CoordRealignment_var);
    doPacking(b,this->CoordRealignSecurityLevel_var);
    doPacking(b,this->CoordRealignKeyIdMode_var);
    doPacking(b,this->CoordRealignKeySource_var);
    doPacking(b,this->CoordRealignKeyIndex_var);
    doPacking(b,this->BeaconSecurityLevel_var);
    doPacking(b,this->BeaconKeyIdMode_var);
    doPacking(b,this->BeaconKeySource_var);
    doPacking(b,this->BeaconKeyIndex_var);
}

void StartRequest::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->PANId_var);
    doUnpacking(b,this->LogicalChannel_var);
    doUnpacking(b,this->ChannelPage_var);
    doUnpacking(b,this->StartTime_var);
    doUnpacking(b,this->BeaconOrder_var);
    doUnpacking(b,this->SuperframeOrder_var);
    doUnpacking(b,this->PANCoordinator_var);
    doUnpacking(b,this->BatteryLifeExtension_var);
    doUnpacking(b,this->CoordRealignment_var);
    doUnpacking(b,this->CoordRealignSecurityLevel_var);
    doUnpacking(b,this->CoordRealignKeyIdMode_var);
    doUnpacking(b,this->CoordRealignKeySource_var);
    doUnpacking(b,this->CoordRealignKeyIndex_var);
    doUnpacking(b,this->BeaconSecurityLevel_var);
    doUnpacking(b,this->BeaconKeyIdMode_var);
    doUnpacking(b,this->BeaconKeySource_var);
    doUnpacking(b,this->BeaconKeyIndex_var);
}

unsigned short StartRequest::getPANId() const
{
    return PANId_var;
}

void StartRequest::setPANId(unsigned short PANId)
{
    this->PANId_var = PANId;
}

unsigned int StartRequest::getLogicalChannel() const
{
    return LogicalChannel_var;
}

void StartRequest::setLogicalChannel(unsigned int LogicalChannel)
{
    this->LogicalChannel_var = LogicalChannel;
}

unsigned char StartRequest::getChannelPage() const
{
    return ChannelPage_var;
}

void StartRequest::setChannelPage(unsigned char ChannelPage)
{
    this->ChannelPage_var = ChannelPage;
}

unsigned int StartRequest::getStartTime() const
{
    return StartTime_var;
}

void StartRequest::setStartTime(unsigned int StartTime)
{
    this->StartTime_var = StartTime;
}

unsigned char StartRequest::getBeaconOrder() const
{
    return BeaconOrder_var;
}

void StartRequest::setBeaconOrder(unsigned char BeaconOrder)
{
    this->BeaconOrder_var = BeaconOrder;
}

unsigned char StartRequest::getSuperframeOrder() const
{
    return SuperframeOrder_var;
}

void StartRequest::setSuperframeOrder(unsigned char SuperframeOrder)
{
    this->SuperframeOrder_var = SuperframeOrder;
}

bool StartRequest::getPANCoordinator() const
{
    return PANCoordinator_var;
}

void StartRequest::setPANCoordinator(bool PANCoordinator)
{
    this->PANCoordinator_var = PANCoordinator;
}

bool StartRequest::getBatteryLifeExtension() const
{
    return BatteryLifeExtension_var;
}

void StartRequest::setBatteryLifeExtension(bool BatteryLifeExtension)
{
    this->BatteryLifeExtension_var = BatteryLifeExtension;
}

bool StartRequest::getCoordRealignment() const
{
    return CoordRealignment_var;
}

void StartRequest::setCoordRealignment(bool CoordRealignment)
{
    this->CoordRealignment_var = CoordRealignment;
}

unsigned char StartRequest::getCoordRealignSecurityLevel() const
{
    return CoordRealignSecurityLevel_var;
}

void StartRequest::setCoordRealignSecurityLevel(unsigned char CoordRealignSecurityLevel)
{
    this->CoordRealignSecurityLevel_var = CoordRealignSecurityLevel;
}

unsigned char StartRequest::getCoordRealignKeyIdMode() const
{
    return CoordRealignKeyIdMode_var;
}

void StartRequest::setCoordRealignKeyIdMode(unsigned char CoordRealignKeyIdMode)
{
    this->CoordRealignKeyIdMode_var = CoordRealignKeyIdMode;
}

unsigned long StartRequest::getCoordRealignKeySource() const
{
    return CoordRealignKeySource_var;
}

void StartRequest::setCoordRealignKeySource(unsigned long CoordRealignKeySource)
{
    this->CoordRealignKeySource_var = CoordRealignKeySource;
}

unsigned char StartRequest::getCoordRealignKeyIndex() const
{
    return CoordRealignKeyIndex_var;
}

void StartRequest::setCoordRealignKeyIndex(unsigned char CoordRealignKeyIndex)
{
    this->CoordRealignKeyIndex_var = CoordRealignKeyIndex;
}

unsigned char StartRequest::getBeaconSecurityLevel() const
{
    return BeaconSecurityLevel_var;
}

void StartRequest::setBeaconSecurityLevel(unsigned char BeaconSecurityLevel)
{
    this->BeaconSecurityLevel_var = BeaconSecurityLevel;
}

unsigned char StartRequest::getBeaconKeyIdMode() const
{
    return BeaconKeyIdMode_var;
}

void StartRequest::setBeaconKeyIdMode(unsigned char BeaconKeyIdMode)
{
    this->BeaconKeyIdMode_var = BeaconKeyIdMode;
}

unsigned long StartRequest::getBeaconKeySource() const
{
    return BeaconKeySource_var;
}

void StartRequest::setBeaconKeySource(unsigned long BeaconKeySource)
{
    this->BeaconKeySource_var = BeaconKeySource;
}

unsigned char StartRequest::getBeaconKeyIndex() const
{
    return BeaconKeyIndex_var;
}

void StartRequest::setBeaconKeyIndex(unsigned char BeaconKeyIndex)
{
    this->BeaconKeyIndex_var = BeaconKeyIndex;
}

class StartRequestDescriptor : public cClassDescriptor
{
  public:
    StartRequestDescriptor();
    virtual ~StartRequestDescriptor();

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

Register_ClassDescriptor(StartRequestDescriptor);

StartRequestDescriptor::StartRequestDescriptor() : cClassDescriptor("StartRequest", "cMessage")
{
}

StartRequestDescriptor::~StartRequestDescriptor()
{
}

bool StartRequestDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<StartRequest *>(obj)!=NULL;
}

const char *StartRequestDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int StartRequestDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 17+basedesc->getFieldCount(object) : 17;
}

unsigned int StartRequestDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<17) ? fieldTypeFlags[field] : 0;
}

const char *StartRequestDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "PANId",
        "LogicalChannel",
        "ChannelPage",
        "StartTime",
        "BeaconOrder",
        "SuperframeOrder",
        "PANCoordinator",
        "BatteryLifeExtension",
        "CoordRealignment",
        "CoordRealignSecurityLevel",
        "CoordRealignKeyIdMode",
        "CoordRealignKeySource",
        "CoordRealignKeyIndex",
        "BeaconSecurityLevel",
        "BeaconKeyIdMode",
        "BeaconKeySource",
        "BeaconKeyIndex",
    };
    return (field>=0 && field<17) ? fieldNames[field] : NULL;
}

int StartRequestDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='P' && strcmp(fieldName, "PANId")==0) return base+0;
    if (fieldName[0]=='L' && strcmp(fieldName, "LogicalChannel")==0) return base+1;
    if (fieldName[0]=='C' && strcmp(fieldName, "ChannelPage")==0) return base+2;
    if (fieldName[0]=='S' && strcmp(fieldName, "StartTime")==0) return base+3;
    if (fieldName[0]=='B' && strcmp(fieldName, "BeaconOrder")==0) return base+4;
    if (fieldName[0]=='S' && strcmp(fieldName, "SuperframeOrder")==0) return base+5;
    if (fieldName[0]=='P' && strcmp(fieldName, "PANCoordinator")==0) return base+6;
    if (fieldName[0]=='B' && strcmp(fieldName, "BatteryLifeExtension")==0) return base+7;
    if (fieldName[0]=='C' && strcmp(fieldName, "CoordRealignment")==0) return base+8;
    if (fieldName[0]=='C' && strcmp(fieldName, "CoordRealignSecurityLevel")==0) return base+9;
    if (fieldName[0]=='C' && strcmp(fieldName, "CoordRealignKeyIdMode")==0) return base+10;
    if (fieldName[0]=='C' && strcmp(fieldName, "CoordRealignKeySource")==0) return base+11;
    if (fieldName[0]=='C' && strcmp(fieldName, "CoordRealignKeyIndex")==0) return base+12;
    if (fieldName[0]=='B' && strcmp(fieldName, "BeaconSecurityLevel")==0) return base+13;
    if (fieldName[0]=='B' && strcmp(fieldName, "BeaconKeyIdMode")==0) return base+14;
    if (fieldName[0]=='B' && strcmp(fieldName, "BeaconKeySource")==0) return base+15;
    if (fieldName[0]=='B' && strcmp(fieldName, "BeaconKeyIndex")==0) return base+16;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *StartRequestDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
        "unsigned int",
        "unsigned char",
        "unsigned int",
        "unsigned char",
        "unsigned char",
        "bool",
        "bool",
        "bool",
        "unsigned char",
        "unsigned char",
        "unsigned long",
        "unsigned char",
        "unsigned char",
        "unsigned char",
        "unsigned long",
        "unsigned char",
    };
    return (field>=0 && field<17) ? fieldTypeStrings[field] : NULL;
}

const char *StartRequestDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int StartRequestDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    StartRequest *pp = (StartRequest *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string StartRequestDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    StartRequest *pp = (StartRequest *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getPANId());
        case 1: return ulong2string(pp->getLogicalChannel());
        case 2: return ulong2string(pp->getChannelPage());
        case 3: return ulong2string(pp->getStartTime());
        case 4: return ulong2string(pp->getBeaconOrder());
        case 5: return ulong2string(pp->getSuperframeOrder());
        case 6: return bool2string(pp->getPANCoordinator());
        case 7: return bool2string(pp->getBatteryLifeExtension());
        case 8: return bool2string(pp->getCoordRealignment());
        case 9: return ulong2string(pp->getCoordRealignSecurityLevel());
        case 10: return ulong2string(pp->getCoordRealignKeyIdMode());
        case 11: return ulong2string(pp->getCoordRealignKeySource());
        case 12: return ulong2string(pp->getCoordRealignKeyIndex());
        case 13: return ulong2string(pp->getBeaconSecurityLevel());
        case 14: return ulong2string(pp->getBeaconKeyIdMode());
        case 15: return ulong2string(pp->getBeaconKeySource());
        case 16: return ulong2string(pp->getBeaconKeyIndex());
        default: return "";
    }
}

bool StartRequestDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    StartRequest *pp = (StartRequest *)object; (void)pp;
    switch (field) {
        case 0: pp->setPANId(string2ulong(value)); return true;
        case 1: pp->setLogicalChannel(string2ulong(value)); return true;
        case 2: pp->setChannelPage(string2ulong(value)); return true;
        case 3: pp->setStartTime(string2ulong(value)); return true;
        case 4: pp->setBeaconOrder(string2ulong(value)); return true;
        case 5: pp->setSuperframeOrder(string2ulong(value)); return true;
        case 6: pp->setPANCoordinator(string2bool(value)); return true;
        case 7: pp->setBatteryLifeExtension(string2bool(value)); return true;
        case 8: pp->setCoordRealignment(string2bool(value)); return true;
        case 9: pp->setCoordRealignSecurityLevel(string2ulong(value)); return true;
        case 10: pp->setCoordRealignKeyIdMode(string2ulong(value)); return true;
        case 11: pp->setCoordRealignKeySource(string2ulong(value)); return true;
        case 12: pp->setCoordRealignKeyIndex(string2ulong(value)); return true;
        case 13: pp->setBeaconSecurityLevel(string2ulong(value)); return true;
        case 14: pp->setBeaconKeyIdMode(string2ulong(value)); return true;
        case 15: pp->setBeaconKeySource(string2ulong(value)); return true;
        case 16: pp->setBeaconKeyIndex(string2ulong(value)); return true;
        default: return false;
    }
}

const char *StartRequestDescriptor::getFieldStructName(void *object, int field) const
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

void *StartRequestDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    StartRequest *pp = (StartRequest *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(StartConfirm);

StartConfirm::StartConfirm(const char *name, int kind) : ::cMessage(name,kind)
{
    this->status_var = 0;
}

StartConfirm::StartConfirm(const StartConfirm& other) : ::cMessage(other)
{
    copy(other);
}

StartConfirm::~StartConfirm()
{
}

StartConfirm& StartConfirm::operator=(const StartConfirm& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void StartConfirm::copy(const StartConfirm& other)
{
    this->status_var = other.status_var;
}

void StartConfirm::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->status_var);
}

void StartConfirm::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->status_var);
}

unsigned short StartConfirm::getStatus() const
{
    return status_var;
}

void StartConfirm::setStatus(unsigned short status)
{
    this->status_var = status;
}

class StartConfirmDescriptor : public cClassDescriptor
{
  public:
    StartConfirmDescriptor();
    virtual ~StartConfirmDescriptor();

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

Register_ClassDescriptor(StartConfirmDescriptor);

StartConfirmDescriptor::StartConfirmDescriptor() : cClassDescriptor("StartConfirm", "cMessage")
{
}

StartConfirmDescriptor::~StartConfirmDescriptor()
{
}

bool StartConfirmDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<StartConfirm *>(obj)!=NULL;
}

const char *StartConfirmDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int StartConfirmDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int StartConfirmDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *StartConfirmDescriptor::getFieldName(void *object, int field) const
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

int StartConfirmDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *StartConfirmDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *StartConfirmDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "MACenum";
            return NULL;
        default: return NULL;
    }
}

int StartConfirmDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    StartConfirm *pp = (StartConfirm *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string StartConfirmDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    StartConfirm *pp = (StartConfirm *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getStatus());
        default: return "";
    }
}

bool StartConfirmDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    StartConfirm *pp = (StartConfirm *)object; (void)pp;
    switch (field) {
        case 0: pp->setStatus(string2ulong(value)); return true;
        default: return false;
    }
}

const char *StartConfirmDescriptor::getFieldStructName(void *object, int field) const
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

void *StartConfirmDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    StartConfirm *pp = (StartConfirm *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(SyncRequest);

SyncRequest::SyncRequest(const char *name, int kind) : ::cMessage(name,kind)
{
    this->LogicalChannel_var = 0;
    this->ChannelPage_var = 0;
    this->TrackBeacon_var = 0;
}

SyncRequest::SyncRequest(const SyncRequest& other) : ::cMessage(other)
{
    copy(other);
}

SyncRequest::~SyncRequest()
{
}

SyncRequest& SyncRequest::operator=(const SyncRequest& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void SyncRequest::copy(const SyncRequest& other)
{
    this->LogicalChannel_var = other.LogicalChannel_var;
    this->ChannelPage_var = other.ChannelPage_var;
    this->TrackBeacon_var = other.TrackBeacon_var;
}

void SyncRequest::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->LogicalChannel_var);
    doPacking(b,this->ChannelPage_var);
    doPacking(b,this->TrackBeacon_var);
}

void SyncRequest::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->LogicalChannel_var);
    doUnpacking(b,this->ChannelPage_var);
    doUnpacking(b,this->TrackBeacon_var);
}

unsigned int SyncRequest::getLogicalChannel() const
{
    return LogicalChannel_var;
}

void SyncRequest::setLogicalChannel(unsigned int LogicalChannel)
{
    this->LogicalChannel_var = LogicalChannel;
}

unsigned char SyncRequest::getChannelPage() const
{
    return ChannelPage_var;
}

void SyncRequest::setChannelPage(unsigned char ChannelPage)
{
    this->ChannelPage_var = ChannelPage;
}

bool SyncRequest::getTrackBeacon() const
{
    return TrackBeacon_var;
}

void SyncRequest::setTrackBeacon(bool TrackBeacon)
{
    this->TrackBeacon_var = TrackBeacon;
}

class SyncRequestDescriptor : public cClassDescriptor
{
  public:
    SyncRequestDescriptor();
    virtual ~SyncRequestDescriptor();

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

Register_ClassDescriptor(SyncRequestDescriptor);

SyncRequestDescriptor::SyncRequestDescriptor() : cClassDescriptor("SyncRequest", "cMessage")
{
}

SyncRequestDescriptor::~SyncRequestDescriptor()
{
}

bool SyncRequestDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SyncRequest *>(obj)!=NULL;
}

const char *SyncRequestDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SyncRequestDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int SyncRequestDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *SyncRequestDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "LogicalChannel",
        "ChannelPage",
        "TrackBeacon",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int SyncRequestDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='L' && strcmp(fieldName, "LogicalChannel")==0) return base+0;
    if (fieldName[0]=='C' && strcmp(fieldName, "ChannelPage")==0) return base+1;
    if (fieldName[0]=='T' && strcmp(fieldName, "TrackBeacon")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SyncRequestDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",
        "unsigned char",
        "bool",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *SyncRequestDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int SyncRequestDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SyncRequest *pp = (SyncRequest *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SyncRequestDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SyncRequest *pp = (SyncRequest *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getLogicalChannel());
        case 1: return ulong2string(pp->getChannelPage());
        case 2: return bool2string(pp->getTrackBeacon());
        default: return "";
    }
}

bool SyncRequestDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SyncRequest *pp = (SyncRequest *)object; (void)pp;
    switch (field) {
        case 0: pp->setLogicalChannel(string2ulong(value)); return true;
        case 1: pp->setChannelPage(string2ulong(value)); return true;
        case 2: pp->setTrackBeacon(string2bool(value)); return true;
        default: return false;
    }
}

const char *SyncRequestDescriptor::getFieldStructName(void *object, int field) const
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

void *SyncRequestDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SyncRequest *pp = (SyncRequest *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(SyncIndication);

SyncIndication::SyncIndication(const char *name, int kind) : ::cMessage(name,kind)
{
    this->LossReason_var = 0;
    this->PANId_var = 0;
    this->LogicalChannel_var = 0;
    this->ChannelPage_var = 0;
    this->SecurityLevel_var = 0;
    this->KeyIdMode_var = 0;
    this->KeySource_var = 0;
    this->KeyIndex_var = 0;
}

SyncIndication::SyncIndication(const SyncIndication& other) : ::cMessage(other)
{
    copy(other);
}

SyncIndication::~SyncIndication()
{
}

SyncIndication& SyncIndication::operator=(const SyncIndication& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void SyncIndication::copy(const SyncIndication& other)
{
    this->LossReason_var = other.LossReason_var;
    this->PANId_var = other.PANId_var;
    this->LogicalChannel_var = other.LogicalChannel_var;
    this->ChannelPage_var = other.ChannelPage_var;
    this->SecurityLevel_var = other.SecurityLevel_var;
    this->KeyIdMode_var = other.KeyIdMode_var;
    this->KeySource_var = other.KeySource_var;
    this->KeyIndex_var = other.KeyIndex_var;
}

void SyncIndication::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->LossReason_var);
    doPacking(b,this->PANId_var);
    doPacking(b,this->LogicalChannel_var);
    doPacking(b,this->ChannelPage_var);
    doPacking(b,this->SecurityLevel_var);
    doPacking(b,this->KeyIdMode_var);
    doPacking(b,this->KeySource_var);
    doPacking(b,this->KeyIndex_var);
}

void SyncIndication::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->LossReason_var);
    doUnpacking(b,this->PANId_var);
    doUnpacking(b,this->LogicalChannel_var);
    doUnpacking(b,this->ChannelPage_var);
    doUnpacking(b,this->SecurityLevel_var);
    doUnpacking(b,this->KeyIdMode_var);
    doUnpacking(b,this->KeySource_var);
    doUnpacking(b,this->KeyIndex_var);
}

unsigned short SyncIndication::getLossReason() const
{
    return LossReason_var;
}

void SyncIndication::setLossReason(unsigned short LossReason)
{
    this->LossReason_var = LossReason;
}

unsigned short SyncIndication::getPANId() const
{
    return PANId_var;
}

void SyncIndication::setPANId(unsigned short PANId)
{
    this->PANId_var = PANId;
}

unsigned int SyncIndication::getLogicalChannel() const
{
    return LogicalChannel_var;
}

void SyncIndication::setLogicalChannel(unsigned int LogicalChannel)
{
    this->LogicalChannel_var = LogicalChannel;
}

unsigned char SyncIndication::getChannelPage() const
{
    return ChannelPage_var;
}

void SyncIndication::setChannelPage(unsigned char ChannelPage)
{
    this->ChannelPage_var = ChannelPage;
}

unsigned char SyncIndication::getSecurityLevel() const
{
    return SecurityLevel_var;
}

void SyncIndication::setSecurityLevel(unsigned char SecurityLevel)
{
    this->SecurityLevel_var = SecurityLevel;
}

unsigned char SyncIndication::getKeyIdMode() const
{
    return KeyIdMode_var;
}

void SyncIndication::setKeyIdMode(unsigned char KeyIdMode)
{
    this->KeyIdMode_var = KeyIdMode;
}

unsigned long SyncIndication::getKeySource() const
{
    return KeySource_var;
}

void SyncIndication::setKeySource(unsigned long KeySource)
{
    this->KeySource_var = KeySource;
}

unsigned char SyncIndication::getKeyIndex() const
{
    return KeyIndex_var;
}

void SyncIndication::setKeyIndex(unsigned char KeyIndex)
{
    this->KeyIndex_var = KeyIndex;
}

class SyncIndicationDescriptor : public cClassDescriptor
{
  public:
    SyncIndicationDescriptor();
    virtual ~SyncIndicationDescriptor();

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

Register_ClassDescriptor(SyncIndicationDescriptor);

SyncIndicationDescriptor::SyncIndicationDescriptor() : cClassDescriptor("SyncIndication", "cMessage")
{
}

SyncIndicationDescriptor::~SyncIndicationDescriptor()
{
}

bool SyncIndicationDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<SyncIndication *>(obj)!=NULL;
}

const char *SyncIndicationDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int SyncIndicationDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
}

unsigned int SyncIndicationDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *SyncIndicationDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "LossReason",
        "PANId",
        "LogicalChannel",
        "ChannelPage",
        "SecurityLevel",
        "KeyIdMode",
        "KeySource",
        "KeyIndex",
    };
    return (field>=0 && field<8) ? fieldNames[field] : NULL;
}

int SyncIndicationDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='L' && strcmp(fieldName, "LossReason")==0) return base+0;
    if (fieldName[0]=='P' && strcmp(fieldName, "PANId")==0) return base+1;
    if (fieldName[0]=='L' && strcmp(fieldName, "LogicalChannel")==0) return base+2;
    if (fieldName[0]=='C' && strcmp(fieldName, "ChannelPage")==0) return base+3;
    if (fieldName[0]=='S' && strcmp(fieldName, "SecurityLevel")==0) return base+4;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeyIdMode")==0) return base+5;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeySource")==0) return base+6;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeyIndex")==0) return base+7;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *SyncIndicationDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
        "unsigned short",
        "unsigned int",
        "unsigned char",
        "unsigned char",
        "unsigned char",
        "unsigned long",
        "unsigned char",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : NULL;
}

const char *SyncIndicationDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "MACenum";
            return NULL;
        default: return NULL;
    }
}

int SyncIndicationDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    SyncIndication *pp = (SyncIndication *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string SyncIndicationDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    SyncIndication *pp = (SyncIndication *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getLossReason());
        case 1: return ulong2string(pp->getPANId());
        case 2: return ulong2string(pp->getLogicalChannel());
        case 3: return ulong2string(pp->getChannelPage());
        case 4: return ulong2string(pp->getSecurityLevel());
        case 5: return ulong2string(pp->getKeyIdMode());
        case 6: return ulong2string(pp->getKeySource());
        case 7: return ulong2string(pp->getKeyIndex());
        default: return "";
    }
}

bool SyncIndicationDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    SyncIndication *pp = (SyncIndication *)object; (void)pp;
    switch (field) {
        case 0: pp->setLossReason(string2ulong(value)); return true;
        case 1: pp->setPANId(string2ulong(value)); return true;
        case 2: pp->setLogicalChannel(string2ulong(value)); return true;
        case 3: pp->setChannelPage(string2ulong(value)); return true;
        case 4: pp->setSecurityLevel(string2ulong(value)); return true;
        case 5: pp->setKeyIdMode(string2ulong(value)); return true;
        case 6: pp->setKeySource(string2ulong(value)); return true;
        case 7: pp->setKeyIndex(string2ulong(value)); return true;
        default: return false;
    }
}

const char *SyncIndicationDescriptor::getFieldStructName(void *object, int field) const
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

void *SyncIndicationDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    SyncIndication *pp = (SyncIndication *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(PollRequest);

PollRequest::PollRequest(const char *name, int kind) : ::cMessage(name,kind)
{
    this->CoordAddrMode_var = 0;
    this->CoordPANId_var = 0;
    this->SecurityLevel_var = 0;
    this->KeyIdMode_var = 0;
    this->KeySource_var = 0;
    this->KeyIndex_var = 0;
}

PollRequest::PollRequest(const PollRequest& other) : ::cMessage(other)
{
    copy(other);
}

PollRequest::~PollRequest()
{
}

PollRequest& PollRequest::operator=(const PollRequest& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void PollRequest::copy(const PollRequest& other)
{
    this->CoordAddrMode_var = other.CoordAddrMode_var;
    this->CoordPANId_var = other.CoordPANId_var;
    this->CoordAddress_var = other.CoordAddress_var;
    this->SecurityLevel_var = other.SecurityLevel_var;
    this->KeyIdMode_var = other.KeyIdMode_var;
    this->KeySource_var = other.KeySource_var;
    this->KeyIndex_var = other.KeyIndex_var;
}

void PollRequest::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->CoordAddrMode_var);
    doPacking(b,this->CoordPANId_var);
    doPacking(b,this->CoordAddress_var);
    doPacking(b,this->SecurityLevel_var);
    doPacking(b,this->KeyIdMode_var);
    doPacking(b,this->KeySource_var);
    doPacking(b,this->KeyIndex_var);
}

void PollRequest::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->CoordAddrMode_var);
    doUnpacking(b,this->CoordPANId_var);
    doUnpacking(b,this->CoordAddress_var);
    doUnpacking(b,this->SecurityLevel_var);
    doUnpacking(b,this->KeyIdMode_var);
    doUnpacking(b,this->KeySource_var);
    doUnpacking(b,this->KeyIndex_var);
}

unsigned char PollRequest::getCoordAddrMode() const
{
    return CoordAddrMode_var;
}

void PollRequest::setCoordAddrMode(unsigned char CoordAddrMode)
{
    this->CoordAddrMode_var = CoordAddrMode;
}

unsigned short PollRequest::getCoordPANId() const
{
    return CoordPANId_var;
}

void PollRequest::setCoordPANId(unsigned short CoordPANId)
{
    this->CoordPANId_var = CoordPANId;
}

MACAddressExt& PollRequest::getCoordAddress()
{
    return CoordAddress_var;
}

void PollRequest::setCoordAddress(const MACAddressExt& CoordAddress)
{
    this->CoordAddress_var = CoordAddress;
}

unsigned char PollRequest::getSecurityLevel() const
{
    return SecurityLevel_var;
}

void PollRequest::setSecurityLevel(unsigned char SecurityLevel)
{
    this->SecurityLevel_var = SecurityLevel;
}

unsigned char PollRequest::getKeyIdMode() const
{
    return KeyIdMode_var;
}

void PollRequest::setKeyIdMode(unsigned char KeyIdMode)
{
    this->KeyIdMode_var = KeyIdMode;
}

unsigned long PollRequest::getKeySource() const
{
    return KeySource_var;
}

void PollRequest::setKeySource(unsigned long KeySource)
{
    this->KeySource_var = KeySource;
}

unsigned char PollRequest::getKeyIndex() const
{
    return KeyIndex_var;
}

void PollRequest::setKeyIndex(unsigned char KeyIndex)
{
    this->KeyIndex_var = KeyIndex;
}

class PollRequestDescriptor : public cClassDescriptor
{
  public:
    PollRequestDescriptor();
    virtual ~PollRequestDescriptor();

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

Register_ClassDescriptor(PollRequestDescriptor);

PollRequestDescriptor::PollRequestDescriptor() : cClassDescriptor("PollRequest", "cMessage")
{
}

PollRequestDescriptor::~PollRequestDescriptor()
{
}

bool PollRequestDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<PollRequest *>(obj)!=NULL;
}

const char *PollRequestDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int PollRequestDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int PollRequestDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *PollRequestDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "CoordAddrMode",
        "CoordPANId",
        "CoordAddress",
        "SecurityLevel",
        "KeyIdMode",
        "KeySource",
        "KeyIndex",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int PollRequestDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='C' && strcmp(fieldName, "CoordAddrMode")==0) return base+0;
    if (fieldName[0]=='C' && strcmp(fieldName, "CoordPANId")==0) return base+1;
    if (fieldName[0]=='C' && strcmp(fieldName, "CoordAddress")==0) return base+2;
    if (fieldName[0]=='S' && strcmp(fieldName, "SecurityLevel")==0) return base+3;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeyIdMode")==0) return base+4;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeySource")==0) return base+5;
    if (fieldName[0]=='K' && strcmp(fieldName, "KeyIndex")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *PollRequestDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned char",
        "unsigned short",
        "MACAddressExt",
        "unsigned char",
        "unsigned char",
        "unsigned long",
        "unsigned char",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *PollRequestDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int PollRequestDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    PollRequest *pp = (PollRequest *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string PollRequestDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    PollRequest *pp = (PollRequest *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getCoordAddrMode());
        case 1: return ulong2string(pp->getCoordPANId());
        case 2: {std::stringstream out; out << pp->getCoordAddress(); return out.str();}
        case 3: return ulong2string(pp->getSecurityLevel());
        case 4: return ulong2string(pp->getKeyIdMode());
        case 5: return ulong2string(pp->getKeySource());
        case 6: return ulong2string(pp->getKeyIndex());
        default: return "";
    }
}

bool PollRequestDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    PollRequest *pp = (PollRequest *)object; (void)pp;
    switch (field) {
        case 0: pp->setCoordAddrMode(string2ulong(value)); return true;
        case 1: pp->setCoordPANId(string2ulong(value)); return true;
        case 3: pp->setSecurityLevel(string2ulong(value)); return true;
        case 4: pp->setKeyIdMode(string2ulong(value)); return true;
        case 5: pp->setKeySource(string2ulong(value)); return true;
        case 6: pp->setKeyIndex(string2ulong(value)); return true;
        default: return false;
    }
}

const char *PollRequestDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 2: return opp_typename(typeid(MACAddressExt));
        default: return NULL;
    };
}

void *PollRequestDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    PollRequest *pp = (PollRequest *)object; (void)pp;
    switch (field) {
        case 2: return (void *)(&pp->getCoordAddress()); break;
        default: return NULL;
    }
}

Register_Class(PollConfirm);

PollConfirm::PollConfirm(const char *name, int kind) : ::cMessage(name,kind)
{
    this->status_var = 0;
}

PollConfirm::PollConfirm(const PollConfirm& other) : ::cMessage(other)
{
    copy(other);
}

PollConfirm::~PollConfirm()
{
}

PollConfirm& PollConfirm::operator=(const PollConfirm& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void PollConfirm::copy(const PollConfirm& other)
{
    this->status_var = other.status_var;
}

void PollConfirm::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->status_var);
}

void PollConfirm::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->status_var);
}

unsigned short PollConfirm::getStatus() const
{
    return status_var;
}

void PollConfirm::setStatus(unsigned short status)
{
    this->status_var = status;
}

class PollConfirmDescriptor : public cClassDescriptor
{
  public:
    PollConfirmDescriptor();
    virtual ~PollConfirmDescriptor();

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

Register_ClassDescriptor(PollConfirmDescriptor);

PollConfirmDescriptor::PollConfirmDescriptor() : cClassDescriptor("PollConfirm", "cMessage")
{
}

PollConfirmDescriptor::~PollConfirmDescriptor()
{
}

bool PollConfirmDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<PollConfirm *>(obj)!=NULL;
}

const char *PollConfirmDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int PollConfirmDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int PollConfirmDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *PollConfirmDescriptor::getFieldName(void *object, int field) const
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

int PollConfirmDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "status")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *PollConfirmDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *PollConfirmDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "MACenum";
            return NULL;
        default: return NULL;
    }
}

int PollConfirmDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    PollConfirm *pp = (PollConfirm *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string PollConfirmDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    PollConfirm *pp = (PollConfirm *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getStatus());
        default: return "";
    }
}

bool PollConfirmDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    PollConfirm *pp = (PollConfirm *)object; (void)pp;
    switch (field) {
        case 0: pp->setStatus(string2ulong(value)); return true;
        default: return false;
    }
}

const char *PollConfirmDescriptor::getFieldStructName(void *object, int field) const
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

void *PollConfirmDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    PollConfirm *pp = (PollConfirm *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


