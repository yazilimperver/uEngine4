#include "property_item.h"

PropertyItem::PropertyItem() : mName{ "" } {

}

PropertyItem::PropertyItem(const std::string& name, const std::any& value) 
	: mName{ name }
    , mValue{ value } {

}
