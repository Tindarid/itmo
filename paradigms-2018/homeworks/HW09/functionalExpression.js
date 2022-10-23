"use strict";

var operation = function(f) {
    return function() {
        var operands = arguments;
        return function() {
            var newArguments = [];
            for (var i = 0; i < operands.length; i++) {
                newArguments.push(operands[i].apply(null, arguments));
            }
            return f.apply(null, newArguments);
        }
    }
}

var negate = operation(function(a) { return -a; });
var add = operation(function(a, b) { return a + b; });
var subtract = operation(function(a, b) { return a - b; });
var multiply = operation(function(a, b) { return a * b; });
var divide = operation(function(a, b) { return a / b; });
var min3 = operation(function() { return Math.min.apply(null, arguments) });
var max5 = operation(function() { return Math.max.apply(null, arguments) });

var cnst = function(a) {
    return function() {
        return a;
    }
}

var pi = cnst(Math.PI);
var e = cnst(Math.E);

var asso = {"x" : 0,
            "y" : 1,
            "z" : 2,}

var variable = function(a) {
    return function() {
        return arguments[asso[a]];
    }
}

var parse = function(str) {
    var stack = [];
    var operations = { "+" : add, "-" : subtract, "*" : multiply, "/" : divide, "negate" : negate,  "min3" : min3, "max5" : max5, };
    var args = { "+" : 2, "-" : 2, "*" : 2, "/" : 2, "negate" : 1,  "min3" : 3, "max5" : 5, };
    var consts = {"pi" : pi, "e" : e}
    var tokens = str.split(" ").filter(function (temp) {
        return temp.length > 0;
    });
    for (var i = 0; i < tokens.length; ++i) {
        if (tokens[i] in consts) {
            stack.push(consts[tokens[i]]);
        } else if (tokens[i] in operations) {
            var a = [];
            for (var j = 0; j < args[tokens[i]]; ++j) {
                a.push(stack.pop());
            }
            a.reverse();
            stack.push(operations[tokens[i]].apply(null, a));
        } else if (tokens[i] in asso) {
            stack.push(variable(tokens[i]));
        } else {
            stack.push(cnst(parseInt(tokens[i])));
        }
    }
    return stack.pop();
}
