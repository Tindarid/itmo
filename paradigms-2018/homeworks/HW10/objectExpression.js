"use strict";

function Const(c) {
    this.c = c;
}
Const.prototype.evaluate = function() {
    return this.c;
}
Const.prototype.toString = function() {
    return this.c + "";
}

function Variable(v) {
    this.v = v;
}
Variable.prototype.evaluate = function() {
    if (this.v === "x") {
        return arguments[0];
    } else if (this.v === "y") {
        return arguments[1];
    } else if (this.v === "z") {
        return arguments[2];
    } else {
        return 0;
    }
}
Variable.prototype.toString = function() {
    return this.v;
}

function BinaryOperation() {
    var operands = [].slice.call(arguments);
    this.a = operands[0];
    this.b = operands[1];
}
BinaryOperation.prototype.toString = function() {
    return this.a.toString() + " " + this.b.toString() + " " + this.operation;
}

function UnaryOperation() {
    this.a = arguments[0];
}
UnaryOperation.prototype.toString = function() {
    return this.a.toString() + " " + this.operation;
}

function Add() {
    BinaryOperation.apply(this, [].slice.call(arguments));
    this.operation = "+";
}
Add.prototype = Object.create(BinaryOperation.prototype);
Add.prototype.evaluate = function() {
    var operands = [].slice.call(arguments);
    return this.a.evaluate.apply(this.a, operands) + this.b.evaluate.apply(this.b, operands);
}
Add.prototype.toString = function() {
    return BinaryOperation.prototype.toString.apply(this, arguments);
}

function Subtract() {
    BinaryOperation.apply(this, arguments);
    this.operation = "-";
}
Subtract.prototype = Object.create(BinaryOperation.prototype);
Subtract.prototype.evaluate = function() {
    var operands = [].slice.call(arguments);
    return this.a.evaluate.apply(this.a, operands) - this.b.evaluate.apply(this.b, operands);
}
Subtract.prototype.toString = function() {
    return BinaryOperation.prototype.toString.apply(this, arguments);
}

function Multiply() {
    BinaryOperation.apply(this, arguments);
    this.operation = "*";
}
Multiply.prototype = Object.create(BinaryOperation.prototype);
Multiply.prototype.evaluate = function() {
    var operands = [].slice.call(arguments);
    return this.a.evaluate.apply(this.a, operands) * this.b.evaluate.apply(this.b, operands);
}
Multiply.prototype.toString = function() {
    return BinaryOperation.prototype.toString.apply(this, arguments);
}

function Divide() {
    BinaryOperation.apply(this, arguments);
    this.operation = "/";
}
Divide.prototype = Object.create(BinaryOperation.prototype);
Divide.prototype.evaluate = function() {
    var operands = [].slice.call(arguments);
    return this.a.evaluate.apply(this.a, operands) / this.b.evaluate.apply(this.b, operands);
}
Divide.prototype.toString = function() {
    return BinaryOperation.prototype.toString.apply(this, arguments);
}

function Negate() {
    UnaryOperation.apply(this, arguments);
    this.operation = "negate";
}
Negate.prototype = Object.create(BinaryOperation.prototype);
Negate.prototype.evaluate = function() {
    var operands = [].slice.call(arguments);
    return -this.a.evaluate.apply(this.a, operands);
}
Negate.prototype.toString = function() {
    return UnaryOperation.prototype.toString.apply(this, arguments);
}

function Square() {
    UnaryOperation.apply(this, arguments);
    this.operation = "square";
}
Square.prototype = Object.create(BinaryOperation.prototype);
Square.prototype.evaluate = function() {
    var operands = [].slice.call(arguments);
    return Math.pow(this.a.evaluate.apply(this.a, operands), 2);
}
Square.prototype.toString = function() {
    return UnaryOperation.prototype.toString.apply(this, arguments);
}

function Sqrt() {
    UnaryOperation.apply(this, arguments);
    this.operation = "sqrt";
}
Sqrt.prototype = Object.create(BinaryOperation.prototype);
Sqrt.prototype.evaluate = function() {
    var operands = [].slice.call(arguments);
    return Math.pow(Math.abs(this.a.evaluate.apply(this.a, operands)), 1 / 2);
}
Sqrt.prototype.toString = function() {
    return UnaryOperation.prototype.toString.apply(this, arguments);
}

function Power() {
    BinaryOperation.apply(this, arguments);
    this.operation = "pow";
}
Power.prototype = Object.create(BinaryOperation.prototype);
Power.prototype.evaluate = function() {
    var operands = [].slice.call(arguments);
    return Math.pow(this.a.evaluate.apply(this.a, operands), this.b.evaluate.apply(this.b, operands));
}
Power.prototype.toString = function() {
    return BinaryOperation.prototype.toString.apply(this, arguments);
}

function Log() {
    BinaryOperation.apply(this, arguments);
    this.operation = "log";
}
Log.prototype = Object.create(BinaryOperation.prototype);
Log.prototype.evaluate = function() {
    var operands = [].slice.call(arguments);
    return Math.log(Math.abs(this.b.evaluate.apply(this.b, operands))) / Math.log(Math.abs(this.a.evaluate.apply(this.a, operands)));
}
Log.prototype.toString = function() {
    return BinaryOperation.prototype.toString.apply(this, arguments);
}

var parse = function(str) {
    var stack = [];
    var operations = { "+" : Add, "-" : Subtract, "*" : Multiply, "/" : Divide, "negate" : Negate, };
    var args = { "+" : 2, "-" : 2, "*" : 2, "/" : 2, "negate" : 1, };
    var tokens = str.split(" ").filter(function (temp) {
        return temp.length > 0;
    });
    for (var i = 0; i < tokens.length; ++i) {
        if (tokens[i] in operations) {
            var a = [];
            for (var j = 0; j < args[tokens[i]]; ++j) {
                a.push(stack.pop());
            }
            a.reverse();
            var temp = Add();
            stack.push(temp.apply(null, a));
        } else if (tokens[i] === "x" || tokens[i] === "y" || tokens[i] === "z") {
            stack.push(new Variable(tokens[i]));
        } else {
            stack.push(new Const(parseInt(tokens[i])));
        }
    }
    return stack.pop();
}

var expr = parse("2 2 +");
var expr2 = new Add(new Const(2), new Const(2));
println(expr);
println(expr2);
