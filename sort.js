var sortObject = function (obj, comparator) {

    var iterArray = function(arr, toKeyVal, comparator) {
        var result = toKeyVal ? {} : [],
            value = null,
            len = arr.length;

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

    // Arrays
    if ( Array.isArray(obj) ) {
        return iterArray(obj, false, comparator);
    }

    // Objects
    else {
        return iterArray(Object.keys(obj).sort(), true, comparator);
    }

};
