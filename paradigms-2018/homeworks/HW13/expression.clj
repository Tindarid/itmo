(defn operation [f] (fn [& operands] (fn [args] (apply f (map (fn [x] (x args)) operands)))))
(defn constant [a] (fn [m] a))
(defn variable [a] (fn [m] (get m a)))
(def add (operation +))
(def subtract (operation -))
(def divide (operation (fn [x y] (/ (double x) (double y)))))
(def multiply (operation *))
(def negate (operation -))
(def sinh (operation (fn [x] (Math/sinh x))))
(def cosh (operation (fn [x] (Math/cosh x))))
(def rmap { #"[-]?[0-9\.]+" #(str "(constant " %1 ")")
            #"[xyz]"        #(str "(variable \"" %1 "\")")
            #"\+"           "add"
            #"\-\s"         "subtract"
            #"\*"           "multiply"
            #"/"            "divide" })
(defn parseFunction [s] (eval (read-string (reduce-kv clojure.string/replace s rmap))))
