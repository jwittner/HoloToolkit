/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */

#ifndef SWIG_SharingClient_WRAP_H_
#define SWIG_SharingClient_WRAP_H_

class SwigDirector_LogWriter : public XTools::LogWriter, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_LogWriter(JNIEnv *jenv);
    virtual ~SwigDirector_LogWriter();
    virtual void WriteLogEntry(XTools::LogSeverity severity, std::string const &message);
public:
    bool swig_overrides(int n) {
      return (n < 1 ? swig_override[n] : false);
    }
protected:
    bool swig_override[1];
};

class SwigDirector_NetworkConnectionListener : public XTools::NetworkConnectionListener, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_NetworkConnectionListener(JNIEnv *jenv);
    virtual ~SwigDirector_NetworkConnectionListener();
    virtual void OnConnected(XTools::NetworkConnectionPtr const &connection);
    virtual void OnConnectFailed(XTools::NetworkConnectionPtr const &connection);
    virtual void OnDisconnected(XTools::NetworkConnectionPtr const &connection);
    virtual void OnMessageReceived(XTools::NetworkConnectionPtr const &connection, XTools::NetworkInMessage &message);
public:
    bool swig_overrides(int n) {
      return (n < 4 ? swig_override[n] : false);
    }
protected:
    bool swig_override[4];
};

class SwigDirector_IntArrayListener : public XTools::IntArrayListener, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_IntArrayListener(JNIEnv *jenv);
    virtual ~SwigDirector_IntArrayListener();
    virtual void OnValueChanged(XTools::int32 index, XTools::int32 newValue);
    virtual void OnValueInserted(XTools::int32 index, XTools::int32 value);
    virtual void OnValueRemoved(XTools::int32 index, XTools::int32 value);
public:
    bool swig_overrides(int n) {
      return (n < 3 ? swig_override[n] : false);
    }
protected:
    bool swig_override[3];
};

class SwigDirector_ObjectElementListener : public XTools::ObjectElementListener, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_ObjectElementListener(JNIEnv *jenv);
    virtual ~SwigDirector_ObjectElementListener();
    virtual void OnIntElementChanged(XTools::XGuid elementID, XTools::int32 newValue);
    virtual void OnLongElementChanged(XTools::XGuid elementID, XTools::int64 newValue);
    virtual void OnFloatElementChanged(XTools::XGuid elementID, float newValue);
    virtual void OnDoubleElementChanged(XTools::XGuid elementID, double newValue);
    virtual void OnStringElementChanged(XTools::XGuid elementID, XTools::XStringPtr const &newValue);
    virtual void OnElementAdded(XTools::ElementPtr const &element);
    virtual void OnElementDeleted(XTools::ElementPtr const &element);
public:
    bool swig_overrides(int n) {
      return (n < 7 ? swig_override[n] : false);
    }
protected:
    bool swig_override[7];
};

class SwigDirector_SyncListener : public XTools::SyncListener, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_SyncListener(JNIEnv *jenv);
    virtual ~SwigDirector_SyncListener();
    virtual void OnSyncChangesBegin();
    virtual void OnSyncChangesEnd();
public:
    bool swig_overrides(int n) {
      return (n < 2 ? swig_override[n] : false);
    }
protected:
    bool swig_override[2];
};

class SwigDirector_SessionListener : public XTools::SessionListener, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_SessionListener(JNIEnv *jenv);
    virtual ~SwigDirector_SessionListener();
    virtual void OnJoiningSession();
    virtual void OnJoinSucceeded();
    virtual void OnJoinFailed();
    virtual void OnSessionDisconnected();
public:
    bool swig_overrides(int n) {
      return (n < 4 ? swig_override[n] : false);
    }
protected:
    bool swig_override[4];
};

class SwigDirector_SessionManagerListener : public XTools::SessionManagerListener, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_SessionManagerListener(JNIEnv *jenv);
    virtual ~SwigDirector_SessionManagerListener();
    virtual void OnCreateSucceeded(XTools::SessionPtr const &newSession);
    virtual void OnCreateFailed(XTools::XStringPtr const &reason);
    virtual void OnSessionAdded(XTools::SessionPtr const &newSession);
    virtual void OnSessionClosed(XTools::SessionPtr const &session);
    virtual void OnUserJoinedSession(XTools::SessionPtr const &session, XTools::UserPtr const &newUser);
    virtual void OnUserLeftSession(XTools::SessionPtr const &session, XTools::UserPtr const &user);
    virtual void OnUserChanged(XTools::SessionPtr const &session, XTools::UserPtr const &user);
    virtual void OnServerConnected();
    virtual void OnServerDisconnected();
public:
    bool swig_overrides(int n) {
      return (n < 9 ? swig_override[n] : false);
    }
protected:
    bool swig_override[9];
};

class SwigDirector_UserPresenceManagerListener : public XTools::UserPresenceManagerListener, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_UserPresenceManagerListener(JNIEnv *jenv);
    virtual ~SwigDirector_UserPresenceManagerListener();
    virtual void OnUserPresenceChanged(XTools::UserPtr const &user);
public:
    bool swig_overrides(int n) {
      return (n < 1 ? swig_override[n] : false);
    }
protected:
    bool swig_override[1];
};

class SwigDirector_RoomManagerListener : public XTools::RoomManagerListener, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_RoomManagerListener(JNIEnv *jenv);
    virtual ~SwigDirector_RoomManagerListener();
    virtual void OnRoomAdded(XTools::RoomPtr const &newRoom);
    virtual void OnRoomClosed(XTools::RoomPtr const &room);
    virtual void OnUserJoinedRoom(XTools::RoomPtr const &room, XTools::UserID user);
    virtual void OnUserLeftRoom(XTools::RoomPtr const &room, XTools::UserID user);
    virtual void OnAnchorsChanged(XTools::RoomPtr const &room);
    virtual void OnAnchorsDownloaded(bool successful, XTools::AnchorDownloadRequestPtr const &request, XTools::XStringPtr const &failureReason);
    virtual void OnAnchorUploadComplete(bool successful, XTools::XStringPtr const &failureReason);
public:
    bool swig_overrides(int n) {
      return (n < 7 ? swig_override[n] : false);
    }
protected:
    bool swig_override[7];
};

class SwigDirector_PairMaker : public XTools::PairMaker, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_PairMaker(JNIEnv *jenv);
    virtual ~SwigDirector_PairMaker();
    virtual bool IsReceiver();
    virtual XTools::int32 GetAddressCount();
    virtual XTools::XStringPtr GetAddress(XTools::int32 index);
    virtual XTools::uint16 GetPort();
    virtual void Update();
    virtual bool IsReadyToConnect();
    virtual XTools::int32 GetLocalKey();
    virtual XTools::int32 GetRemoteKey();
public:
    bool swig_overrides(int n) {
      return (n < 8 ? swig_override[n] : false);
    }
protected:
    bool swig_override[8];
};

class SwigDirector_PairingListener : public XTools::PairingListener, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_PairingListener(JNIEnv *jenv);
    virtual ~SwigDirector_PairingListener();
    virtual void PairingConnectionSucceeded();
    virtual void PairingConnectionFailed(XTools::PairingResult reason);
public:
    bool swig_overrides(int n) {
      return (n < 2 ? swig_override[n] : false);
    }
protected:
    bool swig_override[2];
};

class SwigDirector_ImageTagLocationListener : public XTools::ImageTagLocationListener, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_ImageTagLocationListener(JNIEnv *jenv);
    virtual ~SwigDirector_ImageTagLocationListener();
    virtual void OnTagLocated(XTools::ImageTagLocationPtr const &location);
    virtual void OnTagLocatingCompleted();
public:
    bool swig_overrides(int n) {
      return (n < 2 ? swig_override[n] : false);
    }
protected:
    bool swig_override[2];
};


#endif
