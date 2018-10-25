//
// Created by ezjakko on 25.10.2018.
//

#ifndef _RESOURCEHOLDER_
#define _RESOURCEHOLDER_

#include <map>
#include <string>
#include <memory>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder {
public:
    void            load(Identifier _id, const std::string& _filename);

    template <typename Parameter>   // few types of values need third param to work ( sound (
    void            load(Identifier _id, const std::string& _filename, const Parameter& _param);

    Resource&        get(Identifier _id);
    const            Resource& get(Identifier _id) const;

private:
    void            insertResrouce(Identifier _id, std::unique_ptr<Resource> _resource);

    std::map<Identifier, std::unique_ptr<Resource>> resourceMap;
};

#include "ResourceHolder.inl"

#endif //NODE_WARS_RESOURCEHOLDER_HPP
