///. include
#include "social_network.hpp"
#include "user.hpp"

///STD include
#include <iostream>

using namespace SocialNetworkNS;

int main()
{
   SocialNetwork social_network = SocialNetwork();
   social_network.AddUser("Andrea", "Rossi");
   social_network.AddUser("Giulia", "Russo");
   social_network.AddUser("Marco", "Ferrari");
   social_network.AddUser("Francesca", "Esposito");
   social_network.AddUser("Matteo", "Bianchi");
   social_network.AddUser("Alessandra", "Romano");
   social_network.AddUser("Davide", "Colombo");
   social_network.AddUser("Chiara", "Ricci");
   social_network.AddUser("Federico", "Marino");
   social_network.AddUser("Sara", "Greco");
   social_network.AddFriendship("Alessandra", "Romano", "Giulia", "Russo");
   social_network.AddFriendship("Giulia", "Russo", "Marco", "Ferrari");
   social_network.AddFriendship("Matteo", "Bianchi", "Davide", "Colombo");
   social_network.AddFriendship("Sara", "Greco","Francesca", "Esposito");
   social_network.AddFriendship("Federico", "Marino", "Alessandra", "Romano");
   social_network.AddFriendship("Francesca", "Esposito", "Matteo", "Bianchi");
   social_network.AddFriendship("Alessandra", "Romano", "Davide", "Colombo");
   social_network.AddFriendship("Chiara", "Ricci", "Federico", "Marino");
   social_network.AddFriendship("Giulia", "Russo", "Davide", "Colombo");
   social_network.AddFriendship("Matteo", "Bianchi", "Federico", "Marino");
   social_network.AddFriendship("Chiara", "Ricci", "Federico", "Marino");
   social_network.AddFriendship("Alessandra", "Romano", "Sara", "Greco");
   social_network.AddFriendship("Chiara", "Ricci","Francesca", "Esposito");
   social_network.AddFriendship("Alessandra", "Romano", "Alessandra", "Romano");

   for(const auto user : social_network.CGetUsers())
   {
      std::cout << "List of friends of " << user.ToString() << std::endl;
      for(const auto user_friend : social_network.CGetFriends(user))
      {
         std::cout << "   " << user_friend.ToString() << std::endl;
      }
      std::cout << "List of friends of friends of friends of " 
                << user.ToString() << std::endl;
      for(const auto user_friend : social_network.CGetFriendsOfFriends(user, 3))
      {
         std::cout << "   " << user_friend.ToString() << std::endl;
      }
   }
   if(social_network.CheckSixDegreeOfSeparation())
   {
      std::cout << "Rule of six degree of separation is valid" << std::endl;
   }
   else
   {
      std::cout << "Rule of six degree of separation is not valid" << std::endl;
   }
   social_network.AddFriendship("Andrea", "Rossi", "Giulia", "Russo");
   if(social_network.CheckSixDegreeOfSeparation())
   {
      std::cout << "Rule of six degree of separation is valid" << std::endl;
   }
   else
   {
      std::cout << "Rule of six degree of separation is not valid" << std::endl;
   }
   return 0;
}
