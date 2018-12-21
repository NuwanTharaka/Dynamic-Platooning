//
// Generated file, do not edit! Created by nedtool 5.1 from veins/modules/messages/TraCITrafficLightMessage.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __VEINS_TRACITRAFFICLIGHTMESSAGE_M_H
#define __VEINS_TRACITRAFFICLIGHTMESSAGE_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0501
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif


namespace Veins {

/**
 * Enum generated from <tt>veins/modules/messages/TraCITrafficLightMessage.msg:24</tt> by nedtool.
 * <pre>
 * enum TrafficLightAtrributeType
 * {
 * 
 *     NONE = 0;
 *     LOGICID = 1;
 *     PHASEID = 2;
 *     SWITCHTIME = 3;
 *     STATE = 4;
 * }
 * </pre>
 */
enum TrafficLightAtrributeType {
    NONE = 0,
    LOGICID = 1,
    PHASEID = 2,
    SWITCHTIME = 3,
    STATE = 4
};

/**
 * Enum generated from <tt>veins/modules/messages/TraCITrafficLightMessage.msg:32</tt> by nedtool.
 * <pre>
 * enum TrafficLightChangeSource
 * {
 * 
 *     UNKNOWN = 0;
 *     SUMO = 1;
 *     LOGIC = 2;
 *     RSU = 3;//If an RSU tries to change the values
 * }
 * </pre>
 */
enum TrafficLightChangeSource {
    UNKNOWN = 0,
    SUMO = 1,
    LOGIC = 2,
    RSU = 3
};

/**
 * Class generated from <tt>veins/modules/messages/TraCITrafficLightMessage.msg:40</tt> by nedtool.
 * <pre>
 * // NOTE: Currently only supports changes of the IDs (due to variation in field types)
 * message TraCITrafficLightMessage
 * {
 *     // traffic light id
 *     string tlId;
 *     // what field/attrbute of the traffic light changed?
 *     int changedAttribute \@enum(TrafficLightAtrributeType);
 *     // value before the change
 *     string oldValue;
 *     // value that is to be set / was newly set
 *     string newValue;
 *     // where did the change originate
 *     int changeSource \@enum(TrafficLightChangeSource);
 * }
 * </pre>
 */
class TraCITrafficLightMessage : public ::omnetpp::cMessage
{
  protected:
    ::omnetpp::opp_string tlId;
    int changedAttribute;
    ::omnetpp::opp_string oldValue;
    ::omnetpp::opp_string newValue;
    int changeSource;

  private:
    void copy(const TraCITrafficLightMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const TraCITrafficLightMessage&);

  public:
    TraCITrafficLightMessage(const char *name=nullptr, short kind=0);
    TraCITrafficLightMessage(const TraCITrafficLightMessage& other);
    virtual ~TraCITrafficLightMessage();
    TraCITrafficLightMessage& operator=(const TraCITrafficLightMessage& other);
    virtual TraCITrafficLightMessage *dup() const override {return new TraCITrafficLightMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual const char * getTlId() const;
    virtual void setTlId(const char * tlId);
    virtual int getChangedAttribute() const;
    virtual void setChangedAttribute(int changedAttribute);
    virtual const char * getOldValue() const;
    virtual void setOldValue(const char * oldValue);
    virtual const char * getNewValue() const;
    virtual void setNewValue(const char * newValue);
    virtual int getChangeSource() const;
    virtual void setChangeSource(int changeSource);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TraCITrafficLightMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TraCITrafficLightMessage& obj) {obj.parsimUnpack(b);}

} // namespace Veins

#endif // ifndef __VEINS_TRACITRAFFICLIGHTMESSAGE_M_H

