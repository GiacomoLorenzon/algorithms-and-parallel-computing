///Header include
#include "user.hpp"

namespace SocialNetworkNS
{
   User::User(const std::string & _name, const std::string & _surname) :
      name(_name),
      surname(_surname)
   {}

   bool User::operator == (const User & other) const
   {
      return this->name == other.name and this->surname == other.surname;
   }

   const std::string & User::CGetName() const 
   {
      return name;
   }

   const std::string & User::CGetSurname() const
   {
      return surname;
   }

   std::string User::ToString() const
   {
      return name + " " + surname;
   }
}
