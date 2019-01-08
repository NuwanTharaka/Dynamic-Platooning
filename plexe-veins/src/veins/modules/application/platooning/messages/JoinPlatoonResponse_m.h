//
// Generated file, do not edit! Created by nedtool 5.1 from veins/modules/application/platooning/messages/JoinPlatoonResponse.msg.
//

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#ifndef __JOINPLATOONRESPONSE_M_H
#define __JOINPLATOONRESPONSE_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0501
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "ManeuverMessage_m.h"
// }}

/**
 * Class generated from <tt>veins/modules/application/platooning/messages/JoinPlatoonResponse.msg:28</tt> by nedtool.
 * <pre>
 * // Response to a JoinRequest.
 * // Is sent from the leader of the Platoon to a possible joiner to answer a
 * // JoinRequest.
 * packet JoinPlatoonResponse extends ManeuverMessage
 * {
 *     // is the joiner allowed to join?
 *     bool permitted;
 * }
 * </pre>
 */
class JoinPlatoonResponse : public ::ManeuverMessage
{
  protected:
    bool permitted;

  private:
    void copy(const JoinPlatoonResponse& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const JoinPlatoonResponse&);

  public:
    JoinPlatoonResponse(const char *name=nullptr, short kind=0);
    JoinPlatoonResponse(const JoinPlatoonResponse& other);
    virtual ~JoinPlatoonResponse();
    JoinPlatoonResponse& operator=(const JoinPlatoonResponse& other);
    virtual JoinPlatoonResponse *dup() const override {return new JoinPlatoonResponse(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual bool getPermitted() const;
    virtual void setPermitted(bool permitted);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const JoinPlatoonResponse& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, JoinPlatoonResponse& obj) {obj.parsimUnpack(b);}


#endif // ifndef __JOINPLATOONRESPONSE_M_H

