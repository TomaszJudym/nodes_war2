template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier _id, const std::string& _filename)
{
    std::unique_ptr<Resource> resource = std::make_unique<Resource>();
    if(!resource->loadFromFile(_filename))
        throw std::runtime_error("ResourceHolder::load - failed to load " + _filename);

    //  if loading successful, insert to map
    insertResrouce(_id, std::move(resource)); // id | unique_ptr -> thus move
}


template <typename Resource, typename Identifier>
template <typename Parameter>   // few types of values need third param to work ( sound )
void ResourceHolder<Resource, Identifier>::load(Identifier _id, const std::string& _filename, const Parameter& _param)
{
    std::unique_ptr<Resource> resource = std::make_unique<Resource>();
    if(!resource->loadFromFile(_filename, _param))                      // parameter used
        throw std::runtime_error("ResourceHolder::load - failed to load " + _filename);

    //  if loading successful, insert to map
    insertResrouce(_id, std::move(resource)); // id | unique_ptr -> thus move
}


template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier _id)
{
    auto found = resourceMap.find(_id);
    assert(found != resourceMap.end());

    return *found->second;
}


template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier _id) const
{
    auto found = resourceMap.find(_id);
    assert(found != resourceMap.end());

    return *found->second;
}


template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResrouce(Identifier _id, std::unique_ptr<Resource> _resource)
{
    auto inserted = resourceMap.insert(std::make_pair(_id, std::move(_resource)));
    assert(inserted.second); // != nullptr
}