///Header include
#include "social_network.hpp"
#include "user.hpp"

///STD include
#include <iostream>

namespace SocialNetworkNS {
size_t SocialNetwork::CUserIndex(const std::string &name,
                                 const std::string &surname) const {
  size_t i;

  User u(name, surname);

  bool found = false;

  for (i = 0; i < users.size() && !found; ++i)
    if (users[i] == u)
      found = true;

  if (found)
    return --i;
  else
    return users.size();
}

void SocialNetwork::AddUser(const std::string &name,
                            const std::string &surname) {
    // se non è già presente
    if(CUserIndex(name, surname) == users.size()){
        // allora aggiungo con zero amici
        User new_user(name, surname);
        users.push_back(new_user);
        friends.push_back({});
        std::printf("User succesfully registered.");
    }
    else
        std::printf("// AddUser error: user already registered. //");
}

const std::vector<User> SocialNetwork::CGetUsers() const {
  return users;
}

const std::vector<User> SocialNetwork::CGetFriends(const User &user) const {
    return CGetFriends(user.CGetName(), user.CGetSurname());
}

const std::vector<User> SocialNetwork::CGetFriends(const std::string &name,
                                                   const std::string &surname) const {
    std::vector<User> ret{};

    size_t index = CUserIndex(name,surname);

    //se esiste
    if(index != users.size()){
        for (size_t j = 0; j<friends[index].size(); ++j)
            ret.push_back(users[friends[index][j]]);
        std::printf(" Friends succesfully found.");
        return ret;
    }
    //se non esiste
    else{
        std::printf("// CGetFriends error: user not found. //");
        return ret;
    }
}

void SocialNetwork::AddFriendship(const std::string &first_name,
                                  const std::string &first_surname,
                                  const std::string &second_name,
                                  const std::string &second_surname){
    // se sono diversi
    if (first_name != second_name && first_surname != second_surname) {
        // se esistono
        size_t size = users.size();
        size_t first_index = CUserIndex(first_name, first_surname);
        size_t second_index = CUserIndex(second_name, second_surname);

        if ( first_index < size && second_index < size) {
            for(size_t j=0; j<friends[first_index].size(); j++)
                if(friends[first_index][j] == second_index) return;
            friends[first_index].push_back(second_index);
            friends[second_index].push_back(first_index);
        }
    }
}


}
