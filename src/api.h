#ifndef API_H_
#define API_H_

#include "libs.h"

class API{
   HTTPClient *objHttp = new HTTPClient();

   String authToken = "$2y$10$ZjMUgPq/BIHz8t.idB5YuepfeRj/ka98vNXp3.O06bi..jaF.IgAS";
   String hostServer = "http://api-fechadura.rochaut.com.br/api";

   // String authToken = "$2y$10$/9hwdg/y9Y7IaFUs4ON5L.s.tg1OOLLcnotaqiIpr7dl9i6eIb/7e";
   // String hostServer = "http://192.168.1.57:8000/api";

   boolean aux_serverOn = false;
public:
   API();
   virtual ~API();

   void setHttp(HTTPClient &objH);

   String getDate();
   boolean serverOn();

   boolean httpOk(String url,String data);

   boolean authByTag(String tag);
   boolean authByLogin(String login,String senha);
   boolean insertNewTag(String tag);
   boolean desableTag(String tag);

   void getTesteHttps();
};

#endif /*API_H_*/
