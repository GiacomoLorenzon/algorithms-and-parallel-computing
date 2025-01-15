#ifndef ITEM_H_
#define ITEM_H_

class Item
{
  double weight;
  double size;
  double value;

public:
  Item (double w, double s, double v)
    : weight (w), size (s), value (v) {}

  double get_size (void) const;
  double get_weight (void) const;
  double get_value (void) const;

  void set_size (double size);
  void set_weight (double weight);
  void set_value (double value);

  void print (void) const;
};

#endif /* ITEM_H_ */
