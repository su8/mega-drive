var iterArray = function(arr, obj, toKeyVal, comparator) {
    var result = toKeyVal ? {} : [],
        value = null;

    arr.forEach(function(elem) {
        value = toKeyVal ? obj[elem] : elem;
        if (value !== null && typeof value === 'object') {
            value = sortObject(value, comparator);
        }
        if (toKeyVal) {
            result[elem] = value;
        } else {
            result.push(value);
        }
    });
    return result;
};

var sortObject = function (obj, comparator) {
    // Arrays
    if ( Array.isArray(obj) ) {
        return iterArray(obj, obj, false, comparator);
    }

    // Objects
    else {
        return iterArray(Object.keys(obj).sort(),
                obj, true, comparator);
    }

};
