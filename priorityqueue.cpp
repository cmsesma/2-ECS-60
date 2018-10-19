#include "priorityqueue.h"

#include <iostream>
#include "json.hpp"

PriorityQueue::PriorityQueue(std::size_t max_size) :
    nodes_(max_size + 1, KeyValuePair()),
    max_size_(max_size),
    size_(0) {
}

void PriorityQueue::insert(Key k) {
  insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv) {
  nodes_.push_back(kv);

  int i = size() - 1;
  heapifyUp(i);
}

KeyValuePair PriorityQueue::min() {
  return nodes_[1];
}

KeyValuePair PriorityQueue::removeMin() {

  removeNode(1);
  return nodes_[1];
}

bool PriorityQueue::isEmpty() const {
  return size_ == 0;
}

size_t PriorityQueue::size() const {
  return size_;
}

nlohmann::json PriorityQueue::JSON() const {
  nlohmann::json result;
  for (size_t i = 1; i <= size_; i++) {
    nlohmann::json node;
    KeyValuePair kv = nodes_[i];
    node["key"] = kv.first;
    node["value"] = kv.second;
    if (i != ROOT) {
      node["parent"] = std::to_string(i / 2);
    }
    if (2 * i <= size_) {
      node["leftChild"] = std::to_string(2 * i);
    }
    if (2 * i + 1 <= size_) {
      node["rightChild"] = std::to_string(2 * i + 1);
    }
    result[std::to_string(i)] = node;
  }
  result["metadata"]["max_size"] = max_size_;
  result["metadata"]["size"] = size_;
  return result;
}


int parentVar(size_t i){
  return ( i - 1 ) / (2) ;
}

int leftChildVar(size_t i){
  return ( i * 2 ) + 1 ;
}

int rightChildVar(size_t i){
  return ( i * 2 ) + 2;
}

void PriorityQueue::heapifyUp(size_t i) {

  if (i && nodes_[parentVar(i)] < nodes_[i]){

    std::swap(nodes_[i], nodes_[parentVar(i)]);

    heapifyUp(parentVar(i));
  }
}

void PriorityQueue::heapifyDown(size_t i) {

  int tempVarI = i;

  if (leftChildVar(i) < size() && nodes_[leftChildVar(i)] < nodes_[i]){
    tempVarI = leftChildVar(i);
  }
  if (rightChildVar(i) < size() && nodes_[rightChildVar(i)] < nodes_[i]){
    tempVarI = rightChildVar(i);
  }
  if (tempVarI != i){
    std::swap(nodes_[i], nodes_[tempVarI]);
    heapifyDown(tempVarI);
  }
}


void PriorityQueue::removeNode(size_t i) {

  nodes_[i] = nodes_.back();

  nodes_.pop_back();

  heapifyDown(i);


}

Key PriorityQueue::getKey(size_t i) {
  return nodes_[i].first;
}
