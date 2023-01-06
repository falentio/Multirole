package main

import (
	"net/http"
	"log"
	_ "embed"
)

//go:embed configs.json
var configJson []byte

func main() {
	h := http.NewServeMux()
	h.HandleFunc("/download/configs.json", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		w.Header().Set("Content-Disposition", "attatchment")
		w.Write(configJson)
	})
	h.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		http.Redirect(w, r, "https://trakteer.id/kevin-falentio/post/edopro-private-server-DX2dA", 307)
	})
	err := http.ListenAndServe(":8080", h)
	if err != nil {
		log.Fatal(err)
	}
}
