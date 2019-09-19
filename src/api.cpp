#include "api.h"

   API::API(){}
   API::~API(){}

   void API::setHttp(HTTPClient &objH)
   {
           this->objHttp = &objH;
   }

   boolean API::httpOk(String url,String data)
   {
      try{
         boolean status = false;
         objHttp->begin(url);
         objHttp->addHeader("Content-Type", "application/json");
         int httpCode = objHttp->POST(data);

         status = (httpCode > 0 && httpCode == HTTP_CODE_OK ) ? true : false;

         objHttp->end();
         return status;
      } catch (...) {
         return false;
      }

   }

   boolean API::authByTag(String tag)
   {
      String url = hostServer+"/auth-by-tag";
      String data =
              "{"
              " \"tag_value\" : \""+tag+"\" ,"
              " \"token\" : \""+authToken+"\" "
              "}";

      // return httpOk(url,data);
      return this->aux_serverOn ? httpOk(url,data) : false;
   }

   boolean API::insertNewTag(String tag)
   {
      String url = hostServer+"/insert-new-tag";
      String data =
              "{"
              " \"tag_value\" : \""+tag+"\" ,"
              " \"token\" : \""+authToken+"\" ,"
              " \"ativo\" : 1 "
              "}";

      // return httpOk(url,data);
      return this->aux_serverOn ? httpOk(url,data) : false;
   }

   boolean API::desableTag(String tag)
   {
      String url = hostServer+"/desable-tag";
      String data =
              "{"
              " \"tag_value\" : \""+tag+"\" ,"
              " \"token\" : \""+authToken+"\" "
              "}";

      // return httpOk(url,data);
      return this->aux_serverOn ? httpOk(url,data) : false;
   }

   String API::getDate()
   {
      String payload = "";
      String url = hostServer+"/get-date";
      String data =
              "{"
              " \"token\" : \""+authToken+"\" "
              "}";

      if(this->aux_serverOn){
         try{
            objHttp->begin(url);
            objHttp->addHeader("Content-Type", "application/json");

            int httpCode = objHttp->POST(data);

            payload = (httpCode > 0 && httpCode == HTTP_CODE_OK ) ? objHttp->getString() : "erro";

            objHttp->end();
            return payload;
         } catch (...) {
            return "erro";
         }
      } else {
         return "erro";
      }
   }

   boolean API::serverOn()
   {
      String url = hostServer+"/server-on";
      String data =
              "{"
              " \"token\" : \""+authToken+"\" "
              "}";

      this->aux_serverOn = httpOk(url,data);

      return this->aux_serverOn;
   }

   boolean API::authByLogin(String login,String senha)
   {
      String url = hostServer+"/auth-by-login";
      String data =
              "{"
              " \"token\" : \""+authToken+"\", "
              " \"login_value\" : \""+login+"\", "
              " \"senha_value\" : \""+senha+"\" "
              "}";

      return this->aux_serverOn ? httpOk(url,data) : false;
      // return httpOk(url,data);
   }

   void API::getTesteHttps()
   {
      String url = "https://api-fechadura.rochaut.com.br/teste";
      objHttp->begin(url);

      int httpCode = objHttp->GET();

      if(httpCode > 0 && httpCode == HTTP_CODE_OK ){
         Serial.println(objHttp->getString());
      } else {
         Serial.println("erro");
      }

      objHttp->end();

   }
