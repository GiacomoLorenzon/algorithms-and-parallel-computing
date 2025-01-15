///Header include
#include "social_network.hpp"
#include "user.hpp"

///STD include
#include <iostream>

namespace SocialNetworkNS
{
   void SocialNetwork::AddUser(const std::string & name, const std::string & surname)
   {
      User user = User(name, surname);
      friendships[user] = std::unordered_set<User>();
   }

   const std::unordered_set<User> SocialNetwork::CGetUsers() const
   {
      std::unordered_set<User> ret;
      for(const auto user : friendships)
      {
         ret.insert(user.first);
      }
      return ret;
   }

   const std::unordered_set<User> & SocialNetwork::CGetFriends(const User & user) const
   {
     return friendships.find(user)->second;
   }

   const std::unordered_set<User> SocialNetwork::CGetFriendsOfFriends(const User & user, const unsigned distance) const
   {
      std::unordered_set<User> ret;
      ret.insert(user);
      for(unsigned int iteration = 0; iteration < distance; iteration++)
      {
        std::unordered_set<User> temp;
         for(const auto current_user : ret)
         {
            const auto friends = CGetFriends(current_user);
            temp.insert(friends.begin(), friends.end());
         }
         ret.swap(temp);
      }

      auto iterator = ret.find(user);
      if(iterator != ret.end())
         ret.erase(iterator);

      return ret;
   }

   bool SocialNetwork::CheckSixDegreeOfSeparation() const
   {
      if(friendships.empty())
         return true;
      for(const auto user : friendships)
      {
         if(CGetFriendsOfFriends(user.first, 6u).size() < friendships.size()-1)
         {
            return false;
         }
      }
      return true;
   }

   void SocialNetwork::AddFriendship(const std::string & first_name, 
   									const std::string & first_surname, 
   									const std::string & second_name, 
   									const std::string & second_surname)
   {
      const User first_user = User(first_name, first_surname);
      const User second_user = User(second_name, second_surname);
      if(friendships.find(first_user) == friendships.end() 
      			or friendships.find(second_user) == friendships.end() 
      			or first_user == second_user)
      { 
         return;
      }
      friendships[first_user].insert(second_user);
      friendships[second_user].insert(first_user);
   }
}
