#ifndef SOCIAL_NETWORK_HPP_
#define SOCIAL_NETWORK_HPP_

///. include
#include "user.hpp"

///STL include
#include <unordered_map>
#include <unordered_set>

namespace SocialNetworkNS
{
   class SocialNetwork
   {
      private:
         ///The existing friendships between users
         std::unordered_map<User, std::unordered_set<User> > friendships;

      public:
         /**
          * Return the set of users
          */
         const std::unordered_set<User> CGetUsers() const;
         /**
          * Get the friends of a user
          * @param user is the user
          * @return the set of his/her friends
          */
         const std::unordered_set<User>  &  CGetFriends(const User & user) const;

         /**
          * Get the friends of friends
          * @param user is the starting user
          * @param distance is the maximum length of friendship chain to be considered
          * @return the set of friends of friends
          */
         const std::unordered_set<User> CGetFriendsOfFriends(const User & user, const unsigned int distance) const;

         /**
          * Check if the social network satisfies the six degree of separation rules
          * @return true if the rule is satisfied, false otherwise
          */
         bool CheckSixDegreeOfSeparation() const;

         /**
          * add a new user to the social network
          * @param name is the name of the user
          * @param surname is the surname of the user
          */
         void AddUser(const std::string & name, const std::string  & surname);

         /**
          * Add a friendship between two users
          * @param first_name is the name of the first user
          * @param first_surname is the surname of the first user
          * @param second_name is the name of the second user
          * @param second_surname is the surname of the second user
          */
         void AddFriendship(const std::string & first_name, 
                            const std::string & first_surname, 
                            const std::string & second_name, 
                            const std::string & second_surname);

   };
}
#endif
