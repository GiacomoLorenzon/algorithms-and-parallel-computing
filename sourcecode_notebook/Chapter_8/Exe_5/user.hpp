#ifndef USER_HPP_
#define USER_HPP_

///STD include
#include <string>

namespace SocialNetworkNS
{
   class User
   {
      private:
         ///The name
         const std::string name;

         ///The surname
         const std::string surname;

      public:
         /**
          * Constructor
          * @param name is the name of the user
          * @param surname is the surname of the user
          */
         User(const std::string & name, const std::string & surname);

         /**
          * Comparison operator
          */
         bool operator == (const User & other) const;

         /**
          * Return the name
          */
         const std::string & CGetName() const;

         /**
          * Return the surname
          */
         const std::string & CGetSurname() const;

         /**
          * Return the name and surname of the user
          */
         std::string ToString() const;
   };
}

namespace std
{
   template <>
      struct hash<SocialNetworkNS::User> : public unary_function<SocialNetworkNS::User, size_t>
      {
         size_t operator()(const SocialNetworkNS::User & user) const
         {
            return std::hash<std::string>{}(user.CGetName() + user.CGetSurname());
         }
      };
}
#endif
