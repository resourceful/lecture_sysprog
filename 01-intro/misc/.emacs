(when (>= emacs-major-version 24)
   (require 'package)
   (package-initialize)
   (add-to-list 'package-archives '("melpa" . "http://melpa.milkbox.net/packages/") t)
   )

(require 'color-theme)
(color-theme-initialize)
(setq color-theme-is-global t)
;(color-theme-classic)
;(color-theme-robin-hood)
(require 'color-theme-solarized)
(color-theme-solarized-dark)
;(color-theme-solarized-light)

;(add-hook 'text-mode-hook 'turn-on-auto-fill)

(global-linum-mode t)

(load "auctex.el" nil t t)

(setq TeX-auto-save t)
(setq TeX-parse-self t)


(set-face-attribute 'default nil :height 220)


;; unfill paragraph and region
(defun unfill-paragraph ()
  (interactive)
  (let ((fill-column (point-max)))
    (fill-paragraph nil)))

(defun unfill-region ()
  (interactive)
  (let ((fill-column (point-max)))
    (fill-region (region-beginning) (region-end) nil)))


;; key bindings in Korean
;; full list on http://wttools.sourceforge.net/emacs-stuff/emacs-keybindings.html
;; movement keys binding w/ korean
(global-set-key (kbd "C-ㅜ") 'next-line)
(global-set-key (kbd "C-ㅔ") 'previous-line)
(global-set-key (kbd "C-ㄹ") 'forward-char)
(global-set-key (kbd "C-ㅠ") 'backward-char)
(global-set-key (kbd "C-ㅇ") 'delete-forward-char)
(global-set-key (kbd "C-ㅌ C-ㄴ") 'save-buffer)
(global-set-key (kbd "C-ㅌ C-ㅊ") 'save-buffers-kill-emacs)
(global-set-key (kbd "C-ㄴ") 'isearch-forward)
(global-set-key (kbd "C-ㄱ") 'isearch-backward)
(global-set-key (kbd "C-ㅎ") 'keyboard-quit)
(global-set-key (kbd "C-ㅁ") 'beginning-of-line)
(global-set-key (kbd "C-ㄷ") 'end-of-line)
(global-set-key (kbd "C-ㅍ") 'scroll-up)
(global-set-key (kbd "M-ㅍ") 'scroll-down)
(global-set-key (kbd "C-ㅏ") 'kill-whole-line)
(global-set-key (kbd "C-ㅈ") 'kill-region)
(global-set-key (kbd "C-M-ㅏ") 'kill-sexp)
(global-set-key (kbd "M-ㅈ") 'copy-region-as-kill-nomark)
(global-set-key (kbd "C-ㅛ") 'yank)
(global-set-key (kbd "C-ㅍ") 'scroll-up)
(global-set-key (kbd "M-ㅍ") 'scroll-down)
(global-set-key (kbd "C-ㅣ") 'recenter)
(global-set-key (kbd "M-ㅂ") 'fill-paragraph)
