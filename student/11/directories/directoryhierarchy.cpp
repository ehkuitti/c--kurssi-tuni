#include "directoryhierarchy.hh"

#include <algorithm>

DirectoryHierarchy::DirectoryHierarchy()
{
}

DirectoryHierarchy::~DirectoryHierarchy()
{
    for (const auto& dir : getAll())
    {
        delete dir;
    }
}

void DirectoryHierarchy::addNewDirectory(
        const std::string &id,
        const std::string &timestamp,
        int size,
        std::ostream &output)
{
    if (getPointer(id) != nullptr)
    {
        output << "Error. Directory already added.\n";
        return;
    }

    auto* directory = new Directory{
        .id_ = id,
        .timestamp_ = timestamp,
        .size_ = size,
    };

    all_.push_back(directory);
}

void DirectoryHierarchy::addRelation(
        const std::string &directory,
        const std::string &parent,
        std::ostream &output)
{
    std::cout << parent << " -> " << directory << "\n";
    Directory* parent_dir = (parent == EMPTY) ? home_ : getPointer(parent);
    Directory* sub_dir = getPointer(directory);

    if (sub_dir == nullptr)
    {
        output << "Error. " << sub_dir << "not found.\n";
        return;
    }
    else if (parent_dir == nullptr)
    {
        output << "Error. " << parent << " not found.\n";
        return;
    }

//    auto it = std::find(all_.begin(), all_.end(), sub_dir);
//    if (it == all_.end())
//    {
//        all_.erase(it);
//    }

    parent_dir->subdirectories_.push_back(sub_dir);
    sub_dir->parent_ = parent_dir;
}

void DirectoryHierarchy::commandPrintWorkingDirectory(std::ostream& output) const
{
    if (working_directory_ == home_)
    {
        output << "/" << home_->id_ << std::endl;
    }

    else
    {
        printPath(working_directory_, output);
        output << std::endl;
    }

//    output << all_.size() << std::endl;
}

void DirectoryHierarchy::commandList(std::ostream &output) const //ls
{
    for (auto& dir : working_directory_->subdirectories_)
    {
        output << (*dir).id_ << ", " << (*dir).timestamp_ << ", " << (*dir).size_ <<  std::endl;
    }
}

bool vectorSorter(Directory* dir1, Directory* dir2)
{
    return dir1->id_ < dir2->id_;
}

void DirectoryHierarchy::commandDiskUsage(std::ostream &output) const
{
    int numberToBeIncreased = 0;

    if (working_directory_ == nullptr)
    {
        return;
    }

    std::vector<Directory*> copy_vector = working_directory_->subdirectories_;

    std::sort(copy_vector.begin(), copy_vector.end(), vectorSorter);

    for (auto dir : copy_vector)
    {
        numberToBeIncreased = 0;
        subdirectoriesRecursively(dir, numberToBeIncreased);
        output << numberToBeIncreased << " /" << dir->id_ << std::endl;
    }
}

void DirectoryHierarchy::commandChangeDirectory(const std::string &id, std::ostream &output)
{
    if (id == "~" or id == "..")
    {
        if (working_directory_ == home_)
        {
            output << "Error. Already at the root." << std::endl;
            return;
        }
        else if (id == "~")
        {
            working_directory_ = home_;
        }

        else if (id == "..")
        {
            working_directory_ = working_directory_->parent_;
        }
    }

    else
    {
        for (Directory* dir : working_directory_->subdirectories_)
        {
            if (dir->id_ == id)
            {
                working_directory_ = dir;
                return;
            }
        }
        output << "Error: ID not found" << std::endl;
    }

}

void DirectoryHierarchy::commandFind(const std::string &id, const int n, std::ostream &output) const
{
    Directory* cur_dir = getPointer(id);
    std::set<std::string> all_paths;
    int max = 0;

    for (auto& dir : cur_dir->subdirectories_)
    {
        recursiveFind(dir, all_paths, id+"/"+dir->id_, n, max);
    }

    for (auto& path : all_paths)
    {
        output << path << "/" << std::endl;
    }

}

void DirectoryHierarchy::commandAsOldAs(const std::string &id, std::ostream &output) const
{
    id.append()
    Directory* cur_dir = getPointer(id);
    std::set<std::string> setToBePrinted;
    std::string aikaleima = cur_dir->timestamp_;

    for (Directory* dir : cur_dir->subdirectories_)
    {
        output << "Id_ on: " << dir->id_ << " ja ID on " << id << std::endl;
        if (dir->id_ == id)
        {
            setToBePrinted.insert(dir->id_);
        }
    }

    for (auto& setItem : setToBePrinted)
    {
        output << setItem << std::endl;
    }

}

void DirectoryHierarchy::commandGreatest(const std::string &id, std::ostream &output) const
{
    for (unsigned long i = 0; i < id.length(); i++) {}
    output << "";
}

void DirectoryHierarchy::commandSmallest(const std::string &id, std::ostream &output) const
{

    for (unsigned long i = 0; i < id.length(); i++) {}
    output << "";
}

Directory *DirectoryHierarchy::getPointer(const std::string &id) const
{
    auto* directory = getPointerRecursive(home_, id);
    if (directory != nullptr)
    {
        return directory;
    }
    for (const auto& dir : all_)
    {
        if (dir->id_ == id)
        {
            return dir;
        }
    }

    return nullptr;
}

Directory *DirectoryHierarchy::getPointerRecursive(Directory *current, const std::string &id) const
{
    if (current->id_ == id)
    {
        return current;
    }

    for (const auto& subdir : current->subdirectories_)
    {
        auto* found_directory = getPointerRecursive(subdir, id);
        if (found_directory != nullptr)
        {
            return found_directory;
        }

    }

    return nullptr;
}

void DirectoryHierarchy::printPath(Directory *dir, std::ostream &output) const
{
    if (dir == nullptr)
    {
        return;
    }

    printPath(dir->parent_, output);

    output << "/" << dir->id_;
}

void DirectoryHierarchy::subdirectoriesRecursively(Directory *dir, int& numberToBeIncreased) const
{
    //Breakpoint

    numberToBeIncreased += (*dir).size_;

    for (Directory* subdir : dir->subdirectories_)
    {
        subdirectoriesRecursively(subdir, numberToBeIncreased);
    }



//    return numberToBeIncreased;

}

void DirectoryHierarchy::recursiveFind(Directory *cur_dir, std::set<std::string> &all_paths, std::string current_path, int n, const int &max) const
{

    for (auto& dir : cur_dir->subdirectories_)
    {
        recursiveFind(dir, all_paths, current_path+"/"+dir->id_, n+1, max);
        all_paths.insert(current_path+"/"+dir->id_);
    }
}

std::vector<Directory *> DirectoryHierarchy::getAll(Directory* current) const
{

    if (current == nullptr)
    {
        current = home_;
    }

    std::vector<Directory*> all = {current};

    for (const auto& sub_dir : current->subdirectories_)
    {
        auto sub_all = getAll(sub_dir);
        for (const auto& directory : sub_all)
        {
            all.push_back(directory);
        }
    }

    return all;
}
