#include "DocumentStore.hpp"

DocumentStore::DocumentStore (std::size_t s):
    docs(s), docsDraft(DRAFT_SIZE), size(s), curr(0), currDraft(0)
{}

DocumentStore::DocumentStore (const DocumentStore& rhs):
    docs(rhs.docs), docsDraft(DRAFT_SIZE), size(rhs.size), curr(rhs.curr), currDraft(0)
{}

DocumentStore& DocumentStore::operator= (const DocumentStore& rhs)
{
    docs = rhs.docs;
    size = rhs.size;
    curr = rhs.curr;
    currDraft = 0;
    return *this;
}

void DocumentStore::addDocument (const Document& doc)
{
    if (curr < size)
        docs[curr++] = doc;
}

void DocumentStore::saveAsDraft (const Document& draft)
{
    if (currDraft < DRAFT_SIZE)
        docsDraft[currDraft++] = draft;
}

void DocumentStore::print () const
{
    std::cout << "List of Documents:" << std::endl;
    for (std::size_t j = 0; j < curr; ++j)
        docs[j].print();

    std::cout << "List of Drafts:" << std::endl;
    for (std::size_t j = 0; j < currDraft; ++j)
        docsDraft[j].print();
}