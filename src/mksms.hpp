#ifndef MKSMS_HPP_INCLUDED
#define MKSMS_HPP_INCLUDED
#define CPPHTTPLIB_OPENSSL_SUPPORT

#include <string>
#include <algorithm>
#include <iostream>

#include "deps/httplib.h"
#include "deps/json.hpp"

using namespace std;
using json = nlohmann::json;

namespace mksms{

enum class Direction {IN=-1, BOTH=0, OUT=1};
template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}



using json = nlohmann::json;

class Contact
{
    public:

        /** @brief (one liner)
          *
          * (documentation goes here)
          */
        Contact(string name, string number)
        {
            this->name = name;
            this->number = number;
        }

        /** @brief (one liner)
          *
          * (documentation goes here)
          */
         Contact(map<string, string> cont_map)
         {
            this->number = cont_map["number"];
            this->name = cont_map["name"];
          }

         /** @brief (one liner)
           *
           * (documentation goes here)
           */
          Contact(json json_cont)
          {
            this->number = json_cont["number"];
            this->name = json_cont["name"];
          }

          /** @brief (one liner)
           *
           * (documentation goes here)
           */
          void setName(string name)
          {
            this->name = name;
          }

          /** @brief (one liner)
           *
           * (documentation goes here)
           */
          void setNumber(string number)
          {
            this->number = number;
          }

          /** @brief (one liner)
           *
           * (documentation goes here)
           */
          string getName(void)
          {
            return this->name;
          }

          /** @brief (one liner)
           *
           * (documentation goes here)
           */
          string getNumber(void)
          {
            return this->number;
          }

        /** @brief (one liner)
          *
          * (documentation goes here)
          */
        json to_json()
        {
          json res;
          res["number"] = this->getNumber();
          res["name"] = this->getName();

          return res;
        }

//        bool operator==(Contact const& c)
//        {
//           if(this->name == "c.getName()"){
//                return true;
//            }
//            else{
//                return false;
//            }
//        }

        virtual ~Contact()
        {

        }

    protected:

    private:
        string name;
        string number;
};



class Message
{
    public:

        /** @brief (one liner)
        *
        * (documentation goes here)
        */
        Message(Contact& contact, const string& body, Direction direction, bool read)
        {
            this->contact = &contact;
            this->body = body;
            this->direction = direction;
            this->read = read;
        }

        /** @brief (one liner)
        *
        * (documentation goes here)
        */
        void setContact(Contact& contact)
        {
          this->contact = &contact;
        }


        /** @brief (one liner)
        *
        * (documentation goes here)
        */
        void setBody(string body)
        {
          this->body = body;
        }

        /** @brief (one liner)
        *
        * (documentation goes here)
        */
        void setDirection(Direction direction)
        {
          this->direction = direction;
        }

        /** @brief (one liner)
        *
        * (documentation goes here)
        */
        void setRead(bool read)
        {
          this->read = read;
        }

        /** @brief (one liner)
        *
        * (documentation goes here)
        */
        Contact* getContact()
        {
          return this->contact;
        }

        /** @brief (one liner)
        *
        * (documentation goes here)
        */
        string getBody()
        {
          return this->body;
        }

        /** @brief (one liner)
        *
        * (documentation goes here)
        */
        Direction getDirection()
        {
          return this->direction;
        }

        /** @brief (one liner)
        *
        * (documentation goes here)
        */
        bool getRead()
        {
          return this->read;
        }

        /** @brief (one liner)
        *
        * (documentation goes here)
        */
        json to_json()
        {
            json msg;
            string str_cont = this->contact->to_json().dump();
            msg["contact"] = str_cont;
            msg["body"] = this->body;
            msg["direction"] = this->direction;
            msg["read"] = this->read;

            return msg;
        }

        virtual ~Message()
        {

        }




    protected:

    private:
        Contact* contact;
        string body;
        bool read;
        Direction direction;
};


class Response
{
    public:

    Response()
    {

    }

        /** @brief (one liner)
          *
          * (documentation goes here)
        */

//        Response(string raw_data)
//        {
//            json raw_data_json = json::parse(raw_data);
//            this->success = raw_data_json["success"];
//            if(raw_data_json["success"]==true)
//            {
//                this->message = "";
//            }
//            else
//            {
//                this->message = raw_data_json["message"];
//            }
//            this->data = json(raw_data_json["data"]);
//        }

        /** @brief (one liner)
          *
          * (documentation goes here)
        */
        Response(bool success, string message, string raw_data)
        {
            this->success = success;
            this->message = message;
            this->data = raw_data;
        }

        virtual ~Response()
        {

        }

         /** @brief (one liner)
          *
          * (documentation goes here)
        */
        void setSuccess(bool success)
        {
          this->success = success;
        }

         /** @brief (one liner)
          *
          * (documentation goes here)
        */
        void setMessage(string message)
        {
          this->message = message;
        }

         /** @brief (one liner)
          *
          * (documentation goes here)
        */
        void setData(string data)
        {
          this->data = data;
        }

         /** @brief (one liner)
          *
          * (documentation goes here)
        */
        bool getSuccess()
        {
          return this->success;
        }

         /** @brief (one liner)
          *
          * (documentation goes here)
        */
        string getMessage()
        {
          return this->message;
        }

         /** @brief (one liner)
          *
          * (documentation goes here)
        */
        string getData()
        {
          return this->data;
        }


    protected:

    private:
        bool success;
        string message;
        string data;
};



class Client
{
    public:
        Client();
        Client(string api_key, string api_hash)
        {
            this->api_hash = api_hash;
            this->api_key = api_key;
        }

        virtual ~Client()
        {

        }

        /** @brief (one liner)
        *
        * (documentation goes here)
        */
        Response start_verify(string number, string name)
        {
            httplib::SSLClient client(this->BASE_URL);
            httplib::Params params;
            params.emplace("number", number);
            params.emplace("name", name);
            params.emplace("api_key", this->api_key);
            params.emplace("api_hash", this->api_hash);

            string endpoint = this->BASE_URL+this->ENDPOINT["start_verify"].dump();


            endpoint.erase(std::remove(endpoint.begin(), endpoint.end(), '\"'), endpoint.end());
            cout<<"La requete a envoyer est: "<<endpoint<<endl;

            auto res = client.Post(endpoint.c_str(), params);
            //mksms::Response rep(true, "Khaleb", res->body);
            //return rep;
        }

        /** @brief (one liner)
        *
        * (documentation goes here)
        */
        Response confirm_verify(string number, string code)
        {
            httplib::SSLClient client(this->BASE_URL);
            httplib::Params params;
            params.emplace("number", number);
            params.emplace("code", code);
            params.emplace("api_key", this->api_key);
            params.emplace("api_hash", this->api_hash);
            string endpoint;
            endpoint = this->BASE_URL+this->ENDPOINT["confirm_verify"].dump();
            auto res = client.Post(endpoint.c_str(), params);
            //return mksms::Response(true, "Khaleb", "Only for testing purpose!");

        }

        /** @brief (one liner)
        *
        * (documentation goes here)
        */
        vector<Message> get_messages(time_t min_date, Direction direction, bool read, time_t timestamp)
        {
            httplib::SSLClient client(this->BASE_URL);
            string endpoint = this->BASE_URL+this->ENDPOINT["get_sms"].dump();
            httplib::Params params;
            params.emplace("direction", to_string(as_integer(direction)));
            params.emplace("read", to_string(read));
            params.emplace("timestamps", to_string(timestamp));
            params.emplace("api_key", this->api_key);
            params.emplace("api_hash", this->api_hash);
            auto res = client.Post(endpoint.c_str(), params);
            return vector<Message>();
        }

        /** @brief (one liner)
        *
        * (documentation goes here)
        */
        Response send_message(Message message)
        {
            httplib::SSLClient client(this->BASE_URL);
            string endpoint = this->BASE_URL+this->ENDPOINT["send_sms"].dump();
            httplib::Params params;
            json msg = message.to_json();
            params.emplace("body", msg["body"]);
            params.emplace("contact", msg["contact"]);
            params.emplace("direction", msg["direction"]);
            params.emplace("read", msg["read"]);
            params.emplace("api_key", this->api_key);
            params.emplace("api_hash", this->api_hash);
            auto res = client.Post(endpoint.c_str(), params);

            //Response<string> rep();
            //return rep;

        }

        /** @brief (one liner)
        *
        * (documentation goes here)
        */
        string getApi_key()
        {
          return this->api_key;
        }

        /** @brief (one liner)
        *
        * (documentation goes here)
        */
        string getApi_hash()
        {
          return this->api_hash;
        }

        /** @brief (one liner)
        *
        * (documentation goes here)
        */
        void setApi_key(string api_key)
        {
          this->api_key = api_key;
        }

        /** @brief (one liner)
        *
        * (documentation goes here)
        */
        void setApi_hash(string api_hash)
        {
          this->api_hash = api_hash;
        }


    private:
        const char* BASE_URL = "api.mksms.cm/v1";
        json ENDPOINT = json::parse("{\"send_sms\":\"/sms/send/\",\
                \"get_sms\":\"/sms/available/\", \
                \"start_verify\":\"/phone/verify/start/\",\
                \"confirm_verify\":\"/phone/verify/confirm/\"}");
        string api_hash;
        string api_key;
};


} //namespace mksms

#endif // MKSMS_HPP_INCLUDED




