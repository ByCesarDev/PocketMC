/*!
 * ╔═══════════════════════════════════════════════════════════╗
 * ║  VELA JS — Mini Framework JavaScript                      ║
 * ║  v1.0.0 · Complemento de Vela CSS                        ║
 * ║  ─────────────────────────────────────────────────────── ║
 * ║  Módulos:                                                  ║
 * ║    · DOM      → $(), $$(), create(), html(), attr()       ║
 * ║    · Events   → on(), off(), emit(), ready()              ║
 * ║    · Reveal   → Scroll-reveal con IntersectionObserver   ║
 * ║    · Toast    → Notificaciones tipo toast                 ║
 * ║    · Modal    → Sistema de modales                        ║
 * ║    · Tabs     → Navegación por pestañas                   ║
 * ║    · Accordion→ Paneles colapsables                       ║
 * ║    · Dropdown → Menús desplegables                        ║
 * ║    · Form     → Validación y estados de formularios       ║
 * ║    · Theme    → Toggle dark/light mode                    ║
 * ║    · Navbar   → Comportamiento en scroll                  ║
 * ║    · Utils    → debounce, throttle, storage, copyText     ║
 * ╚═══════════════════════════════════════════════════════════╝
 *
 * Uso básico:
 *   // Auto-init al cargar el DOM:
 *   <script src="assets/js/index.js" defer></script>
 *
 *   // O inicializar manualmente:
 *   Vela.init();
 *
 * Atributos HTML data-vela-*:
 *   data-vela-reveal          → anima al entrar en viewport
 *   data-vela-toast           → dispara un toast al hacer click
 *   data-vela-modal="id"      → abre un modal
 *   data-vela-dismiss         → cierra el modal/toast padre
 *   data-vela-tab             → elemento tab (grupo via data-vela-group)
 *   data-vela-accordion       → toggle de accordion
 *   data-vela-dropdown        → toggle de dropdown
 *   data-vela-theme-toggle    → alterna dark/light mode
 *   data-vela-ripple          → efecto ripple al hacer click
 *   data-vela-copy            → copia el contenido al portapapeles
 *   data-vela-count-up        → anima un número al entrar en viewport
 */

(function (global) {
  'use strict';

  /* ──────────────────────────────────────────────────────────
   * ESTADO INTERNO
   * ────────────────────────────────────────────────────────── */
  const _state = {
    toastQueue: [],
    openModals: [],
    initialized: false,
  };

  const scriptTag = document.currentScript || document.querySelector('script[src*="index.js"]');
  const scriptSrc = scriptTag ? scriptTag.getAttribute('src') : '';
  const basePath = scriptSrc.replace('assets/js/index.js', '');


  /* ══════════════════════════════════════════════════════════
   * 1. DOM — Utilidades de selección y manipulación
   * ════════════════════════════════════════════════════════== */
  const DOM = {
    /**
     * Selecciona un elemento. Alias de querySelector.
     * @param {string} selector
     * @param {Element} [ctx=document]
     */
    $(selector, ctx = document) {
      return ctx.querySelector(selector);
    },

    /**
     * Selecciona múltiples elementos. Retorna Array (no NodeList).
     * @param {string} selector
     * @param {Element} [ctx=document]
     */
    $$(selector, ctx = document) {
      return Array.from(ctx.querySelectorAll(selector));
    },

    /**
     * Crea un elemento con opciones.
     * @param {string} tag - etiqueta HTML
     * @param {Object} [opts] - { class, id, attrs, text, html, children }
     */
    create(tag, opts = {}) {
      const el = document.createElement(tag);
      if (opts.class)    el.className = opts.class;
      if (opts.id)       el.id = opts.id;
      if (opts.text)     el.textContent = opts.text;
      if (opts.html)     el.innerHTML = opts.html;
      if (opts.attrs)    Object.entries(opts.attrs).forEach(([k, v]) => el.setAttribute(k, v));
      if (opts.children) opts.children.forEach(c => el.appendChild(c));
      return el;
    },

    /**
     * Establece o obtiene el innerHTML de un elemento.
     */
    html(el, content) {
      if (content === undefined) return el.innerHTML;
      el.innerHTML = content;
      return el;
    },

    /**
     * Establece o obtiene un atributo.
     */
    attr(el, key, value) {
      if (value === undefined) return el.getAttribute(key);
      el.setAttribute(key, value);
      return el;
    },

    /**
     * Añade/quita/tiene clase(s).
     */
    addClass(el, ...classes)    { el.classList.add(...classes); },
    removeClass(el, ...classes) { el.classList.remove(...classes); },
    toggleClass(el, cls)        { el.classList.toggle(cls); },
    hasClass(el, cls)           { return el.classList.contains(cls); },

    /**
     * Aplica estilos inline como objeto.
     */
    css(el, styles) {
      Object.assign(el.style, styles);
      return el;
    },

    /**
     * Devuelve el elemento padre más cercano que cumpla el selector.
     */
    closest(el, selector) {
      return el.closest(selector);
    },

    /**
     * Elimina un elemento del DOM.
     */
    remove(el) {
      el?.parentNode?.removeChild(el);
    },

    /**
     * Inserta un elemento después de otro.
     */
    after(el, newEl) {
      el.parentNode?.insertBefore(newEl, el.nextSibling);
    },

    /**
     * Inserta un elemento antes de otro.
     */
    before(el, newEl) {
      el.parentNode?.insertBefore(newEl, el);
    },
  };

  /* ══════════════════════════════════════════════════════════
   * 2. EVENTS — Sistema de eventos
   * ════════════════════════════════════════════════════════== */
  const Events = {
    /**
     * Añade un listener. Soporta delegación con `delegate`.
     * @param {Element|string} target
     * @param {string} event
     * @param {Function} handler
     * @param {string|Object} [delegate] - selector para delegación o opciones
     */
    on(target, event, handler, delegate) {
      const el = typeof target === 'string' ? DOM.$(target) : target;
      if (!el) return;
      if (typeof delegate === 'string') {
        el.addEventListener(event, function (e) {
          const matched = e.target.closest(delegate);
          if (matched) handler.call(matched, e, matched);
        });
      } else {
        el.addEventListener(event, handler, delegate);
      }
    },

    /**
     * Elimina un listener.
     */
    off(target, event, handler) {
      const el = typeof target === 'string' ? DOM.$(target) : target;
      el?.removeEventListener(event, handler);
    },

    /**
     * Emite un CustomEvent en un elemento.
     * @param {Element} el
     * @param {string} name
     * @param {*} [detail]
     */
    emit(el, name, detail) {
      el.dispatchEvent(new CustomEvent(`vela:${name}`, { detail, bubbles: true }));
    },

    /**
     * Callback cuando el DOM está listo.
     */
    ready(fn) {
      if (document.readyState !== 'loading') fn();
      else document.addEventListener('DOMContentLoaded', fn);
    },
  };

  /* ══════════════════════════════════════════════════════════
   * 3. REVEAL — Animaciones al hacer scroll
   * ════════════════════════════════════════════════════════== */
  const Reveal = {
    defaults: {
      threshold: 0.15,
      rootMargin: '0px 0px -40px 0px',
      animation: 'animate-fade-in-up',
      once: true,
    },

    /**
     * Observa elementos con [data-vela-reveal] y los anima al entrar en viewport.
     */
    init(options = {}) {
      const cfg = { ...this.defaults, ...options };
      const elements = DOM.$$('[data-vela-reveal]');
      if (!elements.length) return;

      const observer = new IntersectionObserver((entries) => {
        entries.forEach(entry => {
          if (entry.isIntersecting) {
            const el = entry.target;
            const anim = el.dataset.velaReveal || cfg.animation;
            const delay = el.dataset.velaDelay || '';

            el.style.opacity = '';
            el.style.transform = '';
            DOM.addClass(el, anim);
            if (delay) DOM.addClass(el, `delay-${delay}`);

            if (cfg.once) observer.unobserve(el);
          } else if (!cfg.once) {
            const el = entry.target;
            const anim = el.dataset.velaReveal || cfg.animation;
            DOM.removeClass(el, anim);
          }
        });
      }, { threshold: cfg.threshold, rootMargin: cfg.rootMargin });

      elements.forEach(el => {
        el.style.opacity = '0';
        el.style.transform = 'translateY(1rem)';
        el.style.transition = 'none';
        observer.observe(el);
      });
    },
  };

  /* ══════════════════════════════════════════════════════════
   * 4. TOAST — Notificaciones
   * ════════════════════════════════════════════════════════== */
  const Toast = {
    _container: null,

    _getContainer() {
      if (!this._container) {
        this._container = DOM.create('div', {
          id: 'vela-toast-container',
          attrs: { role: 'status', 'aria-live': 'polite' },
        });
        DOM.css(this._container, {
          position: 'fixed',
          top: '1.25rem',
          right: '1.25rem',
          zIndex: '9999',
          display: 'flex',
          flexDirection: 'column',
          gap: '0.625rem',
          pointerEvents: 'none',
        });
        document.body.appendChild(this._container);
      }
      return this._container;
    },

    _icons: {
      success: `<img src="${basePath}assets/images/toast-success.svg" width="18" height="18" alt="Success">`,
      danger:  `<img src="${basePath}assets/images/toast-danger.svg" width="18" height="18" alt="Danger">`,
      warning: `<img src="${basePath}assets/images/toast-warning.svg" width="18" height="18" alt="Warning">`,
      info:    `<img src="${basePath}assets/images/toast-info.svg" width="18" height="18" alt="Info">`,
      default: `<img src="${basePath}assets/images/toast-default.svg" width="18" height="18" alt="Default">`,
    },

    /**
     * Muestra un toast.
     * @param {string} message
     * @param {Object} [opts] - { type, duration, title, closable }
     */
    show(message, opts = {}) {
      const {
        type = 'default',
        duration = 3500,
        title = '',
        closable = true,
      } = opts;

      const container = this._getContainer();
      const iconSvg = this._icons[type] || this._icons.default;

      const toast = DOM.create('div', {
        class: `vela-toast vela-toast-${type}`,
      });
      DOM.css(toast, {
        transform: 'translateX(110%)',
        transition: 'transform 350ms cubic-bezier(0.34, 1.56, 0.64, 1), opacity 350ms ease, background 300ms ease, border-color 300ms ease',
        opacity: '0',
      });

      const iconEl = DOM.create('span', {
        class: 'vela-toast-icon',
        html: iconSvg,
        attrs: { 'aria-hidden': 'true' },
      });

      const body = DOM.create('div', { class: 'vela-toast-body' });

      if (title) {
        const titleEl = DOM.create('p', { class: 'vela-toast-title', text: title });
        body.appendChild(titleEl);
      }

      const msgEl = DOM.create('p', { class: 'vela-toast-msg', text: message });
      body.appendChild(msgEl);

      toast.appendChild(iconEl);
      toast.appendChild(body);

      if (closable) {
        const close = DOM.create('button', { class: 'vela-toast-close', text: '×' });
        close.addEventListener('click', () => this._dismiss(toast));
        toast.appendChild(close);
      }

      container.appendChild(toast);

      // Animación de entrada
      requestAnimationFrame(() => {
        requestAnimationFrame(() => {
          DOM.css(toast, { transform: 'translateX(0)', opacity: '1' });
        });
      });

      // Auto-dismiss
      if (duration > 0) {
        setTimeout(() => this._dismiss(toast), duration);
      }

      Events.emit(document, 'toast:show', { message, type });
      return toast;
    },

    _dismiss(toast) {
      DOM.css(toast, { transform: 'translateX(110%)', opacity: '0' });
      setTimeout(() => DOM.remove(toast), 380);
    },

    success(msg, opts = {}) { return this.show(msg, { ...opts, type: 'success' }); },
    danger(msg, opts = {})  { return this.show(msg, { ...opts, type: 'danger' }); },
    warning(msg, opts = {}) { return this.show(msg, { ...opts, type: 'warning' }); },
    info(msg, opts = {})    { return this.show(msg, { ...opts, type: 'info' }); },

    /**
     * Inicializa botones con data-vela-toast.
     * <button data-vela-toast="Mensaje" data-vela-type="success">
     */
    init() {
      Events.on(document, 'click', (e) => {
        const btn = e.target.closest('[data-vela-toast]');
        if (!btn) return;
        this.show(btn.dataset.velaToast, {
          type:  btn.dataset.velaType  || 'default',
          title: btn.dataset.velaTitle || '',
        });
      });
    },
  };

  /* ══════════════════════════════════════════════════════════
   * 5. MODAL — Sistema de modales
   * ════════════════════════════════════════════════════════== */
  const Modal = {
    _overlay: null,

    _getOverlay() {
      if (!this._overlay) {
        this._overlay = DOM.create('div', { id: 'vela-modal-overlay' });
        DOM.css(this._overlay, {
          position: 'fixed',
          inset: '0',
          background: 'rgba(0,0,0,0.45)',
          backdropFilter: 'blur(4px)',
          zIndex: '1000',
          display: 'flex',
          alignItems: 'center',
          justifyContent: 'center',
          padding: '1rem',
          opacity: '0',
          transition: 'opacity 250ms ease',
          visibility: 'hidden',
        });
        document.body.appendChild(this._overlay);
        this._overlay.addEventListener('click', (e) => {
          if (e.target === this._overlay) this.closeAll();
        });
      }
      return this._overlay;
    },

    /**
     * Abre el modal con el id dado.
     * @param {string} id - ID del elemento modal en el DOM
     */
    open(id) {
      const modalEl = DOM.$(`#${id}`);
      if (!modalEl) return console.warn(`[Vela Modal] No se encontró #${id}`);

      const overlay = this._getOverlay();
      overlay.appendChild(modalEl);

      DOM.css(overlay, { visibility: 'visible' });
      requestAnimationFrame(() => {
        requestAnimationFrame(() => {
          DOM.css(overlay, { opacity: '1' });
          DOM.css(modalEl, { transform: 'scale(1)', opacity: '1' });
        });
      });

      document.body.style.overflow = 'hidden';
      _state.openModals.push(id);
      Events.emit(document, 'modal:open', { id });
    },

    /**
     * Cierra el modal con el id dado.
     */
    close(id) {
      const overlay = this._getOverlay();
      const modalEl = DOM.$(`#${id}`, overlay);
      if (!modalEl) return;

      DOM.css(overlay, { opacity: '0' });
      DOM.css(modalEl, { transform: 'scale(0.95)', opacity: '0' });

      setTimeout(() => {
        DOM.css(overlay, { visibility: 'hidden' });
        document.body.appendChild(modalEl);
        document.body.style.overflow = '';
        _state.openModals = _state.openModals.filter(m => m !== id);
        Events.emit(document, 'modal:close', { id });
      }, 260);
    },

    closeAll() {
      [..._state.openModals].forEach(id => this.close(id));
    },

    /**
     * Crea un modal programáticamente.
     * @param {Object} opts - { id, title, content, footer, size }
     */
    create(opts = {}) {
      const { id = 'vela-modal-' + Date.now(), title = '', content = '', footer = '', size = 'md' } = opts;

      const sizes = { sm: '24rem', md: '32rem', lg: '48rem', xl: '60rem', full: '100%' };
      const modal = DOM.create('div', {
        id,
        attrs: { role: 'dialog', 'aria-modal': 'true', 'aria-labelledby': `${id}-title` },
      });

      DOM.css(modal, {
        background: 'white',
        borderRadius: '1rem',
        boxShadow: '0 25px 60px rgb(0 0 0 / .25)',
        width: '100%',
        maxWidth: sizes[size] || sizes.md,
        maxHeight: '85vh',
        overflow: 'hidden',
        display: 'flex',
        flexDirection: 'column',
        transform: 'scale(0.95)',
        opacity: '0',
        transition: 'transform 250ms cubic-bezier(0.34, 1.56, 0.64, 1), opacity 250ms ease',
        fontFamily: 'inherit',
      });

      modal.innerHTML = `
        <div style="display:flex;align-items:center;justify-content:space-between;padding:1.25rem 1.5rem;border-bottom:1px solid #e2e8f0;">
          <h3 id="${id}-title" style="font-size:1.125rem;font-weight:700;color:#0f172a;">${title}</h3>
          <button data-vela-dismiss="${id}" aria-label="Cerrar"
            style="background:none;border:none;cursor:pointer;font-size:1.25rem;color:#64748b;line-height:1;padding:0.25rem;border-radius:0.375rem;transition:background 150ms ease;">
            ×
          </button>
        </div>
        <div style="padding:1.5rem;overflow-y:auto;flex:1;color:#334155;line-height:1.6;">${content}</div>
        ${footer ? `<div style="padding:1rem 1.5rem;border-top:1px solid #e2e8f0;display:flex;gap:0.75rem;justify-content:flex-end;">${footer}</div>` : ''}
      `;

      document.body.appendChild(modal);
      return { id, open: () => this.open(id), close: () => this.close(id) };
    },

    init() {
      // [data-vela-modal="id"] → abre modal al hacer click
      Events.on(document, 'click', (e) => {
        const trigger = e.target.closest('[data-vela-modal]');
        if (trigger) {
          e.preventDefault();
          this.open(trigger.dataset.velaModal);
        }
      });

      // [data-vela-dismiss="id"] → cierra modal
      Events.on(document, 'click', (e) => {
        const dismisser = e.target.closest('[data-vela-dismiss]');
        if (dismisser) {
          this.close(dismisser.dataset.velaDismiss);
        }
      });

      // Cerrar con Escape
      document.addEventListener('keydown', (e) => {
        if (e.key === 'Escape' && _state.openModals.length) this.closeAll();
      });
    },
  };

  /* ══════════════════════════════════════════════════════════
   * 6. TABS — Pestañas
   * ════════════════════════════════════════════════════════== */
  const Tabs = {
    /**
     * Inicializa grupos de tabs.
     * HTML:
     *   <button data-vela-tab data-vela-group="main" data-vela-target="#panel-1">Tab 1</button>
     *   <div id="panel-1" data-vela-tab-panel>...</div>
     */
    init() {
      Events.on(document, 'click', (e) => {
        const tab = e.target.closest('[data-vela-tab]');
        if (!tab) return;

        const group = tab.dataset.velaGroup;
        const target = tab.dataset.velaTarget;

        // Desactivar todos los tabs del grupo
        DOM.$$(`[data-vela-tab][data-vela-group="${group}"]`).forEach(t => {
          DOM.removeClass(t, 'active', 'tab-active');
          t.setAttribute('aria-selected', 'false');
          t.style.borderBottomColor = '';
          t.style.color = '';
          t.style.fontWeight = '';
        });

        // Ocultar todos los panels del grupo
        DOM.$$(`[data-vela-tab-panel][data-vela-group="${group}"]`).forEach(p => {
          p.hidden = true;
          DOM.css(p, { opacity: '0', transform: 'translateY(4px)' });
        });

        // Activar tab seleccionado
        DOM.addClass(tab, 'active', 'tab-active');
        tab.setAttribute('aria-selected', 'true');

        // Mostrar panel correspondiente
        const panel = DOM.$(target);
        if (panel) {
          panel.hidden = false;
          requestAnimationFrame(() => {
            DOM.css(panel, {
              opacity: '1',
              transform: 'translateY(0)',
              transition: 'opacity 250ms ease, transform 250ms ease',
            });
          });
        }

        Events.emit(tab, 'tabs:change', { group, target });
      });
    },
  };

  /* ══════════════════════════════════════════════════════════
   * 7. ACCORDION — Paneles colapsables
   * ════════════════════════════════════════════════════════== */
  const Accordion = {
    /**
     * HTML:
     *   <div data-vela-accordion>
     *     <button data-vela-accordion-trigger>Título</button>
     *     <div data-vela-accordion-content>Contenido</div>
     *   </div>
     */
    init() {
      Events.on(document, 'click', (e) => {
        const trigger = e.target.closest('[data-vela-accordion-trigger]');
        if (!trigger) return;

        const accordion = trigger.closest('[data-vela-accordion]');
        const content = DOM.$('[data-vela-accordion-content]', accordion);
        const icon = DOM.$('[data-vela-accordion-icon]', trigger);
        const isOpen = accordion.dataset.velaOpen === 'true';

        // Cerrar otros acordeones del mismo grupo si es exclusivo
        const group = accordion.dataset.velaGroup;
        if (group) {
          DOM.$$(`[data-vela-accordion][data-vela-group="${group}"]`).forEach(other => {
            if (other !== accordion && other.dataset.velaOpen === 'true') {
              this._close(other);
            }
          });
        }

        if (isOpen) {
          this._close(accordion);
        } else {
          this._open(accordion, content, icon);
        }
      });
    },

    _open(accordion, content, icon) {
      accordion.dataset.velaOpen = 'true';
      content.style.maxHeight = content.scrollHeight + 'px';
      content.style.opacity = '1';
      if (icon) icon.style.transform = 'rotate(180deg)';
      DOM.addClass(accordion, 'accordion-open');
    },

    _close(accordion) {
      accordion.dataset.velaOpen = 'false';
      const content = DOM.$('[data-vela-accordion-content]', accordion);
      const icon = DOM.$('[data-vela-accordion-icon]', accordion);
      if (content) { content.style.maxHeight = '0'; content.style.opacity = '0'; }
      if (icon) icon.style.transform = 'rotate(0deg)';
      DOM.removeClass(accordion, 'accordion-open');
    },

    /**
     * Aplica estilos base al contenido de acordeones en el DOM.
     */
    _applyStyles() {
      DOM.$$('[data-vela-accordion-content]').forEach(el => {
        DOM.css(el, {
          maxHeight: '0',
          overflow: 'hidden',
          opacity: '0',
          transition: 'max-height 350ms ease, opacity 300ms ease',
        });
      });
      DOM.$$('[data-vela-accordion-icon]').forEach(el => {
        DOM.css(el, { display: 'inline-block', transition: 'transform 300ms ease' });
      });
    },
  };

  /* ══════════════════════════════════════════════════════════
   * 8. DROPDOWN — Menús desplegables
   * ════════════════════════════════════════════════════════== */
  const Dropdown = {
    _open: null,

    /**
     * HTML:
     *   <div style="position:relative">
     *     <button data-vela-dropdown="my-menu">Abrir</button>
     *     <div id="my-menu" data-vela-dropdown-menu hidden>...</div>
     *   </div>
     */
    init() {
      Events.on(document, 'click', (e) => {
        const trigger = e.target.closest('[data-vela-dropdown]');

        if (trigger) {
          e.stopPropagation();
          const targetId = trigger.dataset.velaDropdown;
          const menu = DOM.$(`#${targetId}`);
          if (!menu) return;

          const isHidden = menu.hidden;
          this.closeAll();

          if (isHidden) {
            menu.hidden = false;
            requestAnimationFrame(() => {
              DOM.css(menu, { opacity: '1', transform: 'translateY(0)' });
            });
            this._open = menu;
            trigger.setAttribute('aria-expanded', 'true');
          }
          return;
        }

        // Click fuera → cerrar
        this.closeAll();
      });

      // Aplicar estilos base
      DOM.$$('[data-vela-dropdown-menu]').forEach(menu => {
        DOM.css(menu, {
          opacity: '0',
          transform: 'translateY(-6px)',
          transition: 'opacity 200ms ease, transform 200ms ease',
        });
      });
    },

    closeAll() {
      DOM.$$('[data-vela-dropdown-menu]').forEach(menu => {
        if (!menu.hidden) {
          DOM.css(menu, { opacity: '0', transform: 'translateY(-6px)' });
          setTimeout(() => { menu.hidden = true; }, 200);
        }
      });
      DOM.$$('[data-vela-dropdown]').forEach(t => t.setAttribute('aria-expanded', 'false'));
      this._open = null;
    },
  };

  /* ══════════════════════════════════════════════════════════
   * 9. FORM — Validación y estados
   * ════════════════════════════════════════════════════════== */
  const Form = {
    /**
     * Valida un formulario con la API nativa + estilos de Vela CSS.
     * @param {HTMLFormElement} form
     * @param {Object} [rules] - { fieldName: { required, minLength, pattern, message } }
     * @returns {boolean}
     */
    validate(form, rules = {}) {
      let isValid = true;

      this.clearErrors(form);

      const fields = DOM.$$('input, textarea, select', form);
      fields.forEach(field => {
        const name = field.name || field.id;
        const rule = rules[name] || {};
        const value = field.value.trim();
        let error = '';

        if ((rule.required || field.required) && !value) {
          error = rule.message || `Este campo es obligatorio.`;
        } else if (rule.minLength && value.length < rule.minLength) {
          error = rule.message || `Mínimo ${rule.minLength} caracteres.`;
        } else if (rule.maxLength && value.length > rule.maxLength) {
          error = rule.message || `Máximo ${rule.maxLength} caracteres.`;
        } else if (rule.pattern && !new RegExp(rule.pattern).test(value)) {
          error = rule.message || `Formato inválido.`;
        } else if (field.type === 'email' && value && !/^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(value)) {
          error = 'Ingresa un correo válido.';
        }

        if (error) {
          isValid = false;
          this._showError(field, error);
        } else {
          this._showSuccess(field);
        }
      });

      return isValid;
    },

    _showError(field, message) {
      DOM.addClass(field, 'input-error');
      DOM.removeClass(field, 'input-success');
      let err = DOM.$(`[data-vela-error="${field.name || field.id}"]`, field.form || document);
      if (!err) {
        err = DOM.create('p', { text: message });
        DOM.css(err, { color: 'var(--danger)', fontSize: '0.78rem', marginTop: '0.25rem', fontWeight: '500' });
        err.setAttribute('data-vela-error', field.name || field.id);
        DOM.after(field, err);
      } else {
        err.textContent = message;
      }
    },

    _showSuccess(field) {
      DOM.removeClass(field, 'input-error');
      DOM.addClass(field, 'input-success');
      const err = DOM.$(`[data-vela-error="${field.name || field.id}"]`, field.form || document);
      DOM.remove(err);
    },

    clearErrors(form) {
      DOM.$$('.input-error, .input-success', form).forEach(el => {
        DOM.removeClass(el, 'input-error', 'input-success');
      });
      DOM.$$('[data-vela-error]', form).forEach(DOM.remove);
    },

    /**
     * Resetea el formulario y sus estilos.
     */
    reset(form) {
      form.reset();
      this.clearErrors(form);
    },

    /**
     * Pone un botón en estado loading.
     */
    setLoading(btn, loading = true, loadingText = 'Cargando...') {
      if (loading) {
        btn.dataset.velaOrigText = btn.innerHTML;
        btn.disabled = true;
        btn.innerHTML = `<span class="spinner spinner-sm" style="border-top-color:currentColor;border-color:rgba(255,255,255,.3);border-top-color:white;"></span> ${loadingText}`;
      } else {
        btn.disabled = false;
        btn.innerHTML = btn.dataset.velaOrigText || btn.innerHTML;
      }
    },
  };

  /* ══════════════════════════════════════════════════════════
   * 10. THEME — Toggle Dark / Light mode
   * ════════════════════════════════════════════════════════== */
  const Theme = {
    _key: 'vela-theme',

    get() {
      return localStorage.getItem(this._key) || 'light';
    },

    set(mode) {
      localStorage.setItem(this._key, mode);
      const root = document.documentElement;
      if (mode === 'dark') {
        DOM.addClass(root, 'dark');
        DOM.addClass(document.body, 'dark');
      } else {
        DOM.removeClass(root, 'dark');
        DOM.removeClass(document.body, 'dark');
      }
      const sunSvg = `<img src="${basePath}assets/images/sun.svg" width="18" height="18" alt="Sun">`;
      const moonSvg = `<img src="${basePath}assets/images/moon.svg" width="18" height="18" alt="Moon">`;

      DOM.$$('[data-vela-theme-icon]').forEach(el => {
        el.innerHTML = mode === 'dark' ? sunSvg : moonSvg;
      });
      Events.emit(document, 'theme:change', { mode });
    },

    toggle() {
      this.set(this.get() === 'dark' ? 'light' : 'dark');
    },

    init() {
      // Aplicar tema guardado
      this.set(this.get());

      // Detectar preferencia del sistema si no hay preferencia guardada
      if (!localStorage.getItem(this._key)) {
        const prefersDark = window.matchMedia('(prefers-color-scheme: dark)').matches;
        if (prefersDark) this.set('dark');
      }

      // Botones [data-vela-theme-toggle]
      Events.on(document, 'click', (e) => {
        if (e.target.closest('[data-vela-theme-toggle]')) this.toggle();
      });
    },
  };

  /* ══════════════════════════════════════════════════════════
   * 11. NAVBAR — Comportamiento en scroll
   * ════════════════════════════════════════════════════════== */
  const Navbar = {
    /**
     * Oculta/muestra la navbar al hacer scroll.
     * Añade sombra al bajar de la posición inicial.
     * @param {string|Element} selector - selector del navbar
     */
    init(selector = '[data-vela-navbar], .navbar, nav') {
      const nav = typeof selector === 'string' ? DOM.$(selector) : selector;
      if (!nav) return;

      let lastScroll = 0;
      let hidden = false;

      const hideOnScroll = nav.hasAttribute('data-vela-navbar-hide');

      window.addEventListener('scroll', Utils.throttle(() => {
        const current = window.scrollY;

        // Sombra al desplazarse
        if (current > 10) {
          nav.style.boxShadow = '0 4px 20px rgb(0 0 0 / .08)';
        } else {
          nav.style.boxShadow = '';
        }

        // Ocultar en scroll hacia abajo
        if (hideOnScroll) {
          if (current > lastScroll && current > 80 && !hidden) {
            nav.style.transform = `translateY(-${nav.offsetHeight + 10}px)`;
            hidden = true;
          } else if (current < lastScroll && hidden) {
            nav.style.transform = 'translateY(0)';
            hidden = false;
          }
        }

        lastScroll = current;
      }, 100));

      if (hideOnScroll) {
        nav.style.transition = 'transform 350ms ease, box-shadow 300ms ease';
      } else {
        nav.style.transition = 'box-shadow 300ms ease';
      }
    },
  };

  /* ══════════════════════════════════════════════════════════
   * 12. COUNT-UP — Animar números al entrar en viewport
   * ════════════════════════════════════════════════════════== */
  const CountUp = {
    /**
     * HTML: <span data-vela-count-up data-vela-target="1500" data-vela-suffix="+">0</span>
     */
    init() {
      const elements = DOM.$$('[data-vela-count-up]');
      if (!elements.length) return;

      const observer = new IntersectionObserver((entries) => {
        entries.forEach(entry => {
          if (entry.isIntersecting) {
            this._animate(entry.target);
            observer.unobserve(entry.target);
          }
        });
      }, { threshold: 0.5 });

      elements.forEach(el => observer.observe(el));
    },

    _animate(el) {
      const target = parseInt(el.dataset.velaTarget || el.textContent, 10);
      const duration = parseInt(el.dataset.velaDuration || 1500, 10);
      const suffix = el.dataset.velaSuffix || '';
      const prefix = el.dataset.velaPrefix || '';
      const start = Date.now();
      const from = parseInt(el.dataset.velaFrom || 0, 10);

      const update = () => {
        const elapsed = Date.now() - start;
        const progress = Math.min(elapsed / duration, 1);
        // Easing: ease-out
        const eased = 1 - Math.pow(1 - progress, 3);
        const current = Math.round(from + (target - from) * eased);
        el.textContent = prefix + current.toLocaleString() + suffix;
        if (progress < 1) requestAnimationFrame(update);
      };
      requestAnimationFrame(update);
    },
  };

  /* ══════════════════════════════════════════════════════════
   * 13. RIPPLE — Efecto de onda al hacer click
   * ════════════════════════════════════════════════════════== */
  const Ripple = {
    /**
     * HTML: <button data-vela-ripple>Botón</button>
     */
    init() {
      Events.on(document, 'click', (e) => {
        const el = e.target.closest('[data-vela-ripple]');
        if (!el) return;

        const rect = el.getBoundingClientRect();
        const x = e.clientX - rect.left;
        const y = e.clientY - rect.top;
        const size = Math.max(rect.width, rect.height) * 2;

        const ripple = DOM.create('span');
        DOM.css(ripple, {
          position: 'absolute',
          width: size + 'px',
          height: size + 'px',
          left: (x - size / 2) + 'px',
          top: (y - size / 2) + 'px',
          background: 'rgba(255,255,255,0.35)',
          borderRadius: '50%',
          transform: 'scale(0)',
          animation: 'vela-ripple 600ms linear',
          pointerEvents: 'none',
        });

        const prevPos = el.style.position;
        el.style.position = 'relative';
        el.style.overflow = 'hidden';
        el.appendChild(ripple);

        setTimeout(() => {
          DOM.remove(ripple);
          if (!prevPos) el.style.position = '';
        }, 650);
      });

      // Inyectar keyframe si no existe
      if (!DOM.$('#vela-ripple-style')) {
        const style = DOM.create('style', { id: 'vela-ripple-style' });
        style.textContent = `@keyframes vela-ripple { to { transform: scale(1); opacity: 0; } }`;
        document.head.appendChild(style);
      }
    },
  };

  /* ══════════════════════════════════════════════════════════
   * 14. COPY — Copiar texto al portapapeles
   * ════════════════════════════════════════════════════════== */
  const Copy = {
    /**
     * HTML: <button data-vela-copy="Texto a copiar">Copiar</button>
     *   o:  <button data-vela-copy data-vela-copy-target="#mi-input">Copiar</button>
     */
    init() {
      Events.on(document, 'click', async (e) => {
        const btn = e.target.closest('[data-vela-copy]');
        if (!btn) return;

        let text = btn.dataset.velaCopy;
        if (!text) {
          const target = DOM.$(btn.dataset.velaCopyTarget);
          text = target?.value || target?.textContent || '';
        }

        if (!text) return;

        try {
          await navigator.clipboard.writeText(text);
          const original = btn.innerHTML;
          btn.innerHTML = '✓ Copiado';
          setTimeout(() => { btn.innerHTML = original; }, 2000);
          Toast.success('Copiado al portapapeles', { duration: 2000 });
        } catch {
          Toast.danger('No se pudo copiar');
        }
      });
    },
  };

  /* ══════════════════════════════════════════════════════════
   * 15. UTILS — Utilidades generales
   * ════════════════════════════════════════════════════════== */
  const Utils = {
    /**
     * Retrasa la ejecución de fn hasta que pasen `ms` milisegundos
     * sin que se llame de nuevo.
     */
    debounce(fn, ms = 300) {
      let timer;
      return function (...args) {
        clearTimeout(timer);
        timer = setTimeout(() => fn.apply(this, args), ms);
      };
    },

    /**
     * Ejecuta fn como máximo una vez cada `ms` milisegundos.
     */
    throttle(fn, ms = 200) {
      let last = 0;
      return function (...args) {
        const now = Date.now();
        if (now - last >= ms) {
          last = now;
          fn.apply(this, args);
        }
      };
    },

    /**
     * localStorage helpers con JSON automático.
     */
    storage: {
      get(key, fallback = null) {
        try { return JSON.parse(localStorage.getItem(key)) ?? fallback; }
        catch { return fallback; }
      },
      set(key, value) {
        try { localStorage.setItem(key, JSON.stringify(value)); }
        catch { console.warn('[Vela] storage.set falló'); }
      },
      remove(key) { localStorage.removeItem(key); },
      clear()     { localStorage.clear(); },
    },

    /**
     * Formatea un número con separadores.
     */
    formatNumber(n, locale = 'es-ES') {
      return new Intl.NumberFormat(locale).format(n);
    },

    /**
     * Genera un ID único.
     */
    uid(prefix = 'vela') {
      return `${prefix}-${Math.random().toString(36).slice(2, 8)}`;
    },

    /**
     * Hace fetch con JSON por defecto y manejo de errores.
     */
    async fetch(url, opts = {}) {
      const defaults = {
        headers: { 'Content-Type': 'application/json', 'Accept': 'application/json' },
      };
      try {
        const res = await fetch(url, { ...defaults, ...opts });
        const data = await res.json().catch(() => ({}));
        if (!res.ok) throw new Error(data.message || `HTTP ${res.status}`);
        return { ok: true, data, status: res.status };
      } catch (err) {
        return { ok: false, error: err.message, data: null };
      }
    },

    /**
     * Smooth scroll hacia un elemento.
     */
    scrollTo(target, offset = 0) {
      const el = typeof target === 'string' ? DOM.$(target) : target;
      if (!el) return;
      const top = el.getBoundingClientRect().top + window.scrollY - offset;
      window.scrollTo({ top, behavior: 'smooth' });
    },
  };

  /* ══════════════════════════════════════════════════════════
   * 16. SMOOTH SCROLL — Links internos
   * ════════════════════════════════════════════════════════== */
  const SmoothScroll = {
    init(offset = 72) {
      Events.on(document, 'click', (e) => {
        const link = e.target.closest('a[href^="#"]');
        if (!link) return;
        const href = link.getAttribute('href');
        if (href === '#') return;
        const target = DOM.$(href);
        if (target) {
          e.preventDefault();
          Utils.scrollTo(target, offset);
        }
      });
    },
  };

  /* ══════════════════════════════════════════════════════════
   * 17. INPUT SUCCESS STYLE
   * ════════════════════════════════════════════════════════== */
  function _injectInputSuccessStyle() {
    if (DOM.$('#vela-input-style')) return;
    const style = DOM.create('style', { id: 'vela-input-style' });
    style.textContent = `
      .input-success {
        border-color: var(--success) !important;
        box-shadow: 0 0 0 3px rgb(34 197 94 / .15) !important;
      }
    `;
    document.head.appendChild(style);
  }

  /* ══════════════════════════════════════════════════════════
   * 18. INIT — Inicialización automática
   * ════════════════════════════════════════════════════════== */
  function init(options = {}) {
    if (_state.initialized) return;
    _state.initialized = true;

    const cfg = {
      reveal:       true,
      toast:        true,
      modal:        true,
      tabs:         true,
      accordion:    true,
      dropdown:     true,
      theme:        true,
      navbar:       true,
      countUp:      true,
      ripple:       true,
      copy:         true,
      smoothScroll: true,
      navbarOffset: 72,
      ...options,
    };

    _injectInputSuccessStyle();

    if (cfg.reveal)       Reveal.init();
    if (cfg.toast)        Toast.init();
    if (cfg.modal)        Modal.init();
    if (cfg.tabs)         Tabs.init();
    if (cfg.accordion)  { Accordion._applyStyles(); Accordion.init(); }
    if (cfg.dropdown)     Dropdown.init();
    if (cfg.theme)        Theme.init();
    if (cfg.navbar)       Navbar.init();
    if (cfg.countUp)      CountUp.init();
    if (cfg.ripple)       Ripple.init();
    if (cfg.copy)         Copy.init();
    if (cfg.smoothScroll) SmoothScroll.init(cfg.navbarOffset);

    Events.emit(document, 'ready', { version: '1.0.0' });
    console.info('%c⬡ Vela JS v1.0.0 %c inicializado', 'color:#6366f1;font-weight:700;', 'color:gray;');
  }

  /* ══════════════════════════════════════════════════════════
   * API PÚBLICA
   * ════════════════════════════════════════════════════════== */
  const Vela = {
    version: '1.0.0',

    // Módulos
    DOM,
    Events,
    Reveal,
    Toast,
    Modal,
    Tabs,
    Accordion,
    Dropdown,
    Form,
    Theme,
    Navbar,
    CountUp,
    Ripple,
    Copy,
    Utils,
    SmoothScroll,

    // Accesos directos
    $:       DOM.$.bind(DOM),
    $$:      DOM.$$.bind(DOM),
    on:      Events.on.bind(Events),
    emit:    Events.emit.bind(Events),
    ready:   Events.ready.bind(Events),
    toast:   Toast.show.bind(Toast),
    modal:   Modal.create.bind(Modal),
    scrollTo: Utils.scrollTo,

    init,
  };

  // Exponer globalmente
  global.Vela = Vela;

  // Auto-init al cargar el DOM
  Events.ready(() => Vela.init());

})(typeof window !== 'undefined' ? window : this);
