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
Const.prototype.prefix = function() {
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
Variable.prototype.prefix = function() {
    return this.v;
}

function BinaryOperation(a1, b1) {
    this.a = a1;
    this.b = b1;
}
BinaryOperation.prototype.toString = function() {
    return this.a.toString() + " " + this.b.toString() + " " + this.operation;
}
BinaryOperation.prototype.prefix = function() {
    return "(" + this.operation + " " + this.a.prefix() + " " + this.b.prefix() + ")";
}

function UnaryOperation(a1) {
    this.a = a1;
}
UnaryOperation.prototype.toString = function() {
    return this.a.toString() + " " + this.operation;
}
UnaryOperation.prototype.prefix = function() {
    return "(" + this.operation + " " + this.a.prefix() + ")";
}

function Add() {
    BinaryOperation.apply(this, arguments);
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
Add.prototype.prefix = function() {
    return BinaryOperation.prototype.prefix.apply(this, arguments);
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
Subtract.prototype.prefix = function() {
    return BinaryOperation.prototype.prefix.apply(this, arguments);
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
Multiply.prototype.prefix = function() {
    return BinaryOperation.prototype.prefix.apply(this, arguments);
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
Divide.prototype.prefix = function() {
    return BinaryOperation.prototype.prefix.apply(this, arguments);
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
Negate.prototype.prefix = function() {
    return UnaryOperation.prototype.prefix.apply(this, arguments);
}

function ArcTan() {
    UnaryOperation.apply(this, arguments);
    this.operation = "atan";
}
ArcTan.prototype = Object.create(BinaryOperation.prototype);
ArcTan.prototype.evaluate = function() {
    var operands = [].slice.call(arguments);
    return Math.atan(this.a.evaluate.apply(this.a, operands));
}
ArcTan.prototype.toString = function() {
    return UnaryOperation.prototype.toString.apply(this, arguments);
}
ArcTan.prototype.prefix = function() {
    return UnaryOperation.prototype.prefix.apply(this, arguments);
}

function Exp() {
    UnaryOperation.apply(this, arguments);
    this.operation = "exp";
}
Exp.prototype = Object.create(BinaryOperation.prototype);
Exp.prototype.evaluate = function() {
    var operands = [].slice.call(arguments);
    return Math.exp(this.a.evaluate.apply(this.a, operands));
}
Exp.prototype.toString = function() {
    return UnaryOperation.prototype.toString.apply(this, arguments);
}
Exp.prototype.prefix = function() {
    return UnaryOperation.prototype.prefix.apply(this, arguments);
}

function parsePrefix(s) {
    var stack = [];
    var ans = [];
    var balance = 0;
    var ind = 0;

    function process(f) {
        var c = 0;
        while (true) {
            c++;
            var a1 = stack.pop();
            var b1 = stack.pop();
            if (c === 1 && b1 === "(" && a1 === "some" && f === true) {
                throw new SyntaxError("Expression in ()");
            }
            if (b1 === "(" && f === true) {
                stack.push(a1);
                continue;
            } else if (b1 === "(" && f === false) {
                stack.push(a1);
                stack.push(b1);
                break;
            }
            if (isOp(b1)) {
                if (a1 === "some") {
                    if (b1 === "negate") {
                        ans.push(new Negate(ans.pop()));
                        stack.push("some");
                        continue;
                    } else if (b1 === "exp") {
                        ans.push(new Exp(ans.pop()));
                        stack.push("some");
                        continue;
                    } else if (b1 === "atan") {
                        ans.push(new ArcTan(ans.pop()));
                        stack.push("some");
                        continue;
                    }
                } else {
                    if (b1 != undefined) {
                        stack.push(b1);
                    }
                    if (a1 != undefined) {
                        stack.push(a1);
                    }
                    break;
                }
            }
            if (a1 !== "some" || b1 !== "some") {
                if (b1 !== undefined) {
                    stack.push(b1);
                }
                if (a1 !== undefined) {
                    stack.push(a1);
                }
                break;
            } else {
                var op = stack.pop();
                var a = ans.pop();
                var b = ans.pop();
                switch (op) {
                    case "+":
                        ans.push(new Add(b, a));
                        stack.push("some");
                        break;
                    case "-":
                        ans.push(new Subtract(b, a));
                        stack.push("some");
                        break;
                    case "/":
                        ans.push(new Divide(b, a));
                        stack.push("some");
                        break;
                    case "*":
                        ans.push(new Multiply(b, a));
                        stack.push("some");
                        break;
                    default:
                        if (op === "(") {
                            throw new SyntaxError("Two expression in () at pos " + ind);
                        } else if (op === "some") {
                            throw new SyntaxError("Three expression in () at pos " + ind);
                        } else if (op === undefined) {
                            throw new SyntaxError("Excessive info at pos " + ind);
                        }
                        throw new SyntaxError("Too many arguments for " + op + " at pos " + ind);
                }
            }
        }
    }
    function skipWh() {
        while (inString() && s[ind] === " ") {
            ind++;
        }
    }
    function isOp(c) {
        switch (c) {
            case "+":
            case "-":
            case "/":
            case "*":
            case "negate":
            case "atan":
            case "exp":
                return true;
            default:
                return false;
        }
    }
    function isVar(c) {
        if (c === "z" || c === "x" || c === "y") {
            return true;
        }
        return false;
    }
    function checkNumber(temp) {
        for (var i = 0; i < temp.length(); i++) {
            if (temp[i] === "-") {
                if (i !== 0) {
                    throw new SyntaxError("Incorrect constant");
                }
            } else if (!isDigit(temp[i])) {
                return false;
            }
        }
        return true;
    }
    function getSome() {
        var i = ind;
        while (inString() && s[ind] != " " && s[ind] != ")" && s[ind] != "(") {
            ind++;
        }
        return s.substring(i, ind);
    }
    function isDigit(c) {
        if (c >= '0' && c <= '9') {
            return true;
        }
        return false; 
    }
    function inString() {
        if (ind < s.length()) {
            return true;
        }
        return false;
    }

    //println(s);
    if (s === "") {
        throw new SyntaxError("Empty input");
    }
    while (true) {
        skipWh();
        if (!inString()) {
            break;
        }
        if (s[ind] === "(") {
            balance++;
            stack.push("(");
            ind++;
        } else if (s[ind] === ")") {
            balance--;
            if (balance < 0) {
                throw new SyntaxError("Missing left bracket");
            }
            ind++;
            process(true);
        } else if (isDigit(s[ind]) || s[ind] === "-" && isDigit(s[ind + 1])) {
            var temp = getSome();
            if (!checkNumber(temp)) {
                throw new SyntaxError("Incorrect constant");
            }
            stack.push("some");
            ans.push(new Const(+temp));
            if (balance === 0) {
                process(false);
            }
        } else {
            var temp = getSome();
            if (isOp(temp)) {
                stack.push(temp);
            } else if (isVar(temp)) {
                stack.push("some");
                ans.push(new Variable(temp));
                if (balance === 0) {
                    process(false);
                }
            } else {
                throw new SyntaxError("Incorrect variable or operation (" + temp + ") at pos" + ind);
            }
        }
    }
    if (balance > 0) {
        throw new SyntaxError("Missing right bracket at pos" + s.length());
    }
    var expr = ans.pop();
    var k = stack.pop();
    var t = stack.pop();
    if (expr === undefined) {
        if (k === "(") {
            throw new SyntaxError("Empty op at pos " + ind);
        } 
        throw new SyntaxError("Too few arguments for " + k + " at pos " + ind);
    }
    if (t !== undefined) {
        throw new SyntaxError("Too few arguments for " + t + " at pos " + ind);
    }
    if (ans.pop() !== undefined) {
        throw new SyntaxError("Error");
    }
    return expr;
}
