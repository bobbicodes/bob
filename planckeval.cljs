(require '[planck.core :refer [slurp load-string]])
(println (load-string (slurp "eval.bob")))