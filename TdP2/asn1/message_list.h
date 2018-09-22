#ifndef MESSAGELIST_H
#define MESSAGELIST_H

// Common
#define EVENT_MANAGER_STATUS                 "/event/managerstatus"

// IO Manager
#define REQUEST_IO_SETOUTPUT                 "/request/iomanager/setoutput"
#define REQUEST_IO_REGISTEROUTPUT            "/request/iomanager/registeroutput"
#define REQUEST_IO_UNREGISTEROUTPUT          "/request/iomanager/unregisteroutput"
#define STATE_IO_OUTPUTREGISTRATIONCHANGED   "/state/iomanager/outputregistrationchanged"
#define STATE_IO_INPUTCHANGED                "/state/iomanager/inputchanged"
#define STATE_IO_OUTPUTCHANGED               "/state/iomanager/outputchanged"

// Train Manager
#define EVENT_TRAIN_CONNECTED                "/event/trainmanager/trainconnected"
#define EVENT_TRAIN_DISCONNECTED             "/event/trainmanager/traindisconnected"
#define EVENT_TRAIN_STATUS                   "/event/trainmanager/trainstatus"

// TLC Manager
#define REQUEST_TLC_PRIORITY                 "/request/tlcmanager/priorityrequest"
#define STATE_TLC_PRIORITY                   "/state/tlcmanager/priority"

// UCS Manager
#define STATE_UCS_ROUTESTATUS                "/state/ucsmanager/routestatus"
#define REQUEST_UCS_ROUTE                    "/request/ucsmanager/routerequested"
#define EVENT_UCS_ROUTEACK                   "/event/ucsmanager/routeacknowledged"
#define EVENT_UCS_ROUTECREATED               "/event/ucsmanager/routecreated"
#define EVENT_UCS_ROUTECANCELED              "/event/ucsmanager/routecanceled"
#define EVENT_UCS_ROUTEDISABLED              "/event/ucsmanager/routedisabled"

// SignalWarning Manager
#define EVENT_SIGNALWARNING_CLEANAREA        "/event/signalwarning/cleanarea"
#define EVENT_SIGNALWARNING_DEGRADEDAREA     "/event/signalwarning/degradedarea"
#define EVENT_SIGNALWARNING_SIGNALOPENED     "/event/signalwarning/signalopened"
#define EVENT_SIGNALWARNING_SIGNALCLOSED     "/event/signalwarning/signalclosed"

// ITMS Manager
// Empty

// Depot Manager
#define STATE_DEPOT_CONTACT_CHANGED          "/state/depotmanager/contactchanged"

// Manual Switch manager
#define STATE_MANUALSWITCH_SWITCHMOVED       "/state/manualswitchmanager/switchmoved"

// Platform manager
#define STATE_PLATFORM_STATUS                "/state/platformmanager/platformstatus"

#endif
