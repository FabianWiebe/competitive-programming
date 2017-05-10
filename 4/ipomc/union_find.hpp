
template <typnename T>
struct Entry<T> {
	Entry(T value, Entry * parent) : value(value), parent(parent) {}
	size_t value;
	Entry * parent;
	inline bool is_root() {
		return this == parent;
	}
	Entry * get_representative() {
		if (this->is_root()) {
			return this;
		}
		return this->parent = this->parent->get_representative();
	}
	inline bool is_in_same_set(Entry * e) {
		return this->get_representative() == e->get_representative();
	}
};