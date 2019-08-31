#include <iostream>

#include <gtest/gtest.h>
#include "../src/mksms.hpp"
#include <string>





const string api_hash = "73249341d85f566b6f2b8cef4563d6c149efe4df2b43f21776a6c9faf7f61af5";
const string api_key = "830EA3BB2A";
const string name = "Jon Doe";
const string dev_name = "Kouam";
const string number = "657818876";
const string dev_number = "693138363";
const string msg_body = "Hello world!";
const string msg_body2 = "What's up peoples?";

using namespace std;


TEST(Contact, ConstructorWithStrings) {
    
    mksms::Contact contact(name, number);
    EXPECT_EQ(name, contact.getName());
    EXPECT_EQ(number, contact.getNumber());
}

TEST(Contact, ConstructorwithMap) {

    map<string, string> dict;
    dict["number"] = number;
    dict["name"] = name;
    mksms::Contact contact(dict);
    EXPECT_EQ(name, contact.getName());
    EXPECT_EQ(number, contact.getNumber());
}

TEST(Contact, ToJson){
    mksms::Contact contact(name, number);
    string str_form = contact.to_json().dump();
    string expected = "{\"name\":\""+name+"\",\"number\":\""+number+"\"}";
    EXPECT_EQ(expected, str_form);
}

TEST(Message, Constructor){
    mksms::Contact contact(name, number);
    mksms::Message message(contact,  msg_body, mksms::Direction::IN, false);
    //EXPECT_EQ(&contact, message.getContact());
    EXPECT_EQ(msg_body, message.getBody());
    EXPECT_EQ(mksms::Direction::IN, message.getDirection());
    EXPECT_EQ(false, message.getRead());
}


TEST(Message, ToJson){
    mksms::Contact contact(name, number);
    mksms::Message message(contact, msg_body, mksms::Direction::OUT, true);
    string str_form = message.to_json().dump();
    string expected = "{\"body\":\"Hello world!\",\"contact\":\"{\\\"name\\\":\\\"Jon Doe\\\",\\\"number\\\":\\\"657818876\\\"}\",\"direction\":1,\"read\":true}";
    EXPECT_EQ(expected, str_form);
}

TEST(Client, Constructor){
    mksms::Client client(api_key, api_hash);
    EXPECT_EQ(api_key, client.getApi_key());
    EXPECT_EQ(api_hash, client.getApi_hash());
}


TEST(Client, StartVerify){
    mksms::Client client(api_key, api_hash);
    mksms::Response<string> rep = client.start_verify(dev_number, dev_name);

}

TEST(Client, ConfirmVerify){
    mksms::Client client(api_key, api_hash);
    mksms::Response<string> rep = client.confirm_verify(dev_number, dev_name);
}

TEST(Client, GetMessages){
    mksms::Client client(api_key, api_hash);
   
}

TEST(Client, SendMessage){

}