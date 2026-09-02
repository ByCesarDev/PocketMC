// PocketMC Accounts — i18n Localization Engine with Dropdown

const translations = {
  es: {
    'nav.home': 'Inicio',
    'nav.features': 'Características',
    'nav.howToLink': '¿Cómo vincular?',
    'nav.signIn': 'Iniciar sesión',
    'nav.createAccount': 'Crear cuenta →',
    'nav.signOut': 'Cerrar sesión',
    'nav.backProfile': '← Volver al Perfil',

    'hero.badge': '✨ Identidad Global para PocketMC',
    'hero.title1': 'Tu cuenta online para',
    'hero.titleHighlight': 'PocketMC',
    'hero.subtitle': 'Asegura tu Player ID único (UUID permanente), reserva tu @username global y vincula tu perfil desde el juego sin perder el soporte offline.',
    'hero.createBtn': 'Crear cuenta PocketMC',
    'hero.signInBtn': 'Iniciar sesión',
    'hero.welcomeBack': '¡Hola de nuevo, @{username}!',
    'hero.activeSession': 'Sesión online activa',
    'hero.goToProfile': 'Ir a mi perfil PocketMC →',

    'stats.offline': 'Offline Friendly',
    'stats.identity': 'Identidad Permanente',
    'stats.optional': '100% Opcional',
    'stats.reqSuffix': ' Requisitos',
    'stats.reqValue': '0 Requisitos',

    'feat.f1.title': 'Siempre Offline',
    'feat.f1.desc': 'El juego inicia directamente en modo offline local. No dependes de internet para jugar ni para crear mundos.',
    'feat.f2.title': 'Player ID Global',
    'feat.f2.desc': 'Tu UUID único te identificará en servidores, guardados en la nube y funcionalidades multijugador futuras.',
    'feat.f3.title': 'Vinculación In-Game',
    'feat.f3.desc': 'Vincula tu cuenta desde la pantalla Profile en PocketMC en 2 clics sin borrar ningún progreso anterior.',

    'how.badge': 'Paso a paso',
    'how.title': '¿Cómo vincular tu cuenta al juego?',
    'how.subtitle': 'Es un proceso rápido de solo 3 sencillos pasos.',
    'how.s1.title': 'Crea tu cuenta aquí',
    'how.s1.desc': 'Regístrate en esta web eligiendo tu @username único y una contraseña segura.',
    'how.s2.title': 'Abre PocketMC',
    'how.s2.desc': 'En el menú principal entra en Profile y haz clic en Link PocketMC Account.',
    'how.s3.title': '¡Listo para jugar!',
    'how.s3.desc': 'Ingresa tu correo y contraseña. Tu perfil pasará automáticamente al estado Online.',

    'footer.builtWith': 'Desarrollado con',
    'footer.disclaimer': 'PocketMC es un proyecto de código abierto. No está afiliado a Mojang ni Microsoft.',

    'login.title': 'Bienvenido',
    'login.subtitle': 'Inicia sesión en tu cuenta PocketMC',
    'login.email': 'Correo electrónico',
    'login.emailPlaceholder': 'tu@correo.com',
    'login.password': 'Contraseña',
    'login.forgot': '¿Olvidaste tu contraseña?',
    'login.btn': 'Iniciar sesión',
    'login.signingIn': 'Iniciando sesión...',
    'login.noAccount': '¿Aún no tienes cuenta?',
    'login.registerLink': 'Regístrate aquí',
    'login.errFill': 'Por favor completa todos los campos.',
    'login.errAuth': 'Correo o contraseña incorrectos.',
    'login.toastTitle': '¡Bienvenido!',
    'login.toastMsg': 'Sesión iniciada correctamente',

    'reg.title': 'Crear Cuenta',
    'reg.subtitle': 'Tu identidad oficial para PocketMC',
    'reg.username': 'Nombre de usuario (@handle)',
    'reg.usernamePlaceholder': 'Ej: Steve_99 (3-16 caracteres)',
    'reg.displayName': 'Nombre para mostrar (Opcional)',
    'reg.displayNamePlaceholder': 'Ej: Steve',
    'reg.email': 'Correo electrónico',
    'reg.emailPlaceholder': 'tu@correo.com',
    'reg.password': 'Contraseña (mínimo 6 caracteres)',
    'reg.confirmPassword': 'Confirmar contraseña',
    'reg.btn': 'Registrar mi cuenta',
    'reg.creating': 'Creando cuenta...',
    'reg.hasAccount': '¿Ya tienes cuenta?',
    'reg.signInLink': 'Inicia sesión',
    'reg.errUserLength': 'El nombre de usuario debe tener entre 3 y 16 caracteres.',
    'reg.errUserFormat': 'El nombre de usuario solo puede contener letras, números y guion bajo.',
    'reg.errPassLength': 'La contraseña debe tener al menos 6 caracteres.',
    'reg.errPassMatch': 'Las contraseñas no coinciden.',
    'reg.toastTitle': '¡Cuenta creada!',
    'reg.toastMsg': 'Bienvenido a PocketMC Accounts',

    'prof.online': '● Online',
    'prof.editBtn': '✏️ Editar perfil',
    'prof.username': 'Nombre de usuario',
    'prof.displayName': 'Nombre para mostrar',
    'prof.uuid': 'PocketMC Player ID (UUID Permanente)',
    'prof.copyBtn': '📋 Copiar ID',
    'prof.memberSince': 'Miembro desde',
    'prof.email': 'Correo de la cuenta',
    'prof.signOut': 'Cerrar sesión',
    'prof.toastCopyTitle': '¡Copiado!',
    'prof.toastCopyMsg': 'Player ID copiado al portapapeles',

    'edit.title': 'Editar Perfil',
    'edit.subtitle': 'Modifica los datos visibles de tu jugador',
    'edit.username': 'Nombre de usuario (@handle)',
    'edit.displayName': 'Nombre para mostrar',
    'edit.displayNamePlaceholder': 'Nombre en el juego',
    'edit.cancel': 'Cancelar',
    'edit.save': 'Guardar cambios',
    'edit.saving': 'Guardando...',
    'edit.success': '¡Perfil actualizado correctamente!',
    'edit.toastTitle': 'Actualizado',
    'edit.toastMsg': 'Cambios guardados con éxito',

    'forgot.title': 'Recuperar Clave',
    'forgot.subtitle': 'Ingresa tu correo para recibir las instrucciones',
    'forgot.email': 'Correo electrónico',
    'forgot.emailPlaceholder': 'tu@correo.com',
    'forgot.btn': 'Enviar enlace de recuperación',
    'forgot.sending': 'Enviando enlace...',
    'forgot.success': '¡Enlace enviado! Revisa tu bandeja de entrada.',
    'forgot.toastTitle': 'Correo enviado',
    'forgot.toastMsg': 'Instrucciones enviadas con éxito',
    'forgot.backLogin': '← Volver a Iniciar sesión'
  },
  en: {
    'nav.home': 'Home',
    'nav.features': 'Features',
    'nav.howToLink': 'How to link?',
    'nav.signIn': 'Sign In',
    'nav.createAccount': 'Create Account →',
    'nav.signOut': 'Sign Out',
    'nav.backProfile': '← Back to Profile',

    'hero.badge': '✨ Global Identity for PocketMC',
    'hero.title1': 'Your online account for',
    'hero.titleHighlight': 'PocketMC',
    'hero.subtitle': 'Secure your permanent Player ID (UUID), claim your unique @username and link your local profile from inside the game with full offline support.',
    'hero.createBtn': 'Create PocketMC Account',
    'hero.signInBtn': 'Sign In',
    'hero.welcomeBack': 'Welcome back, @{username}!',
    'hero.activeSession': 'Active online session',
    'hero.goToProfile': 'Go to my PocketMC Profile →',

    'stats.offline': 'Offline Friendly',
    'stats.identity': 'Permanent Identity',
    'stats.optional': '100% Optional',
    'stats.reqSuffix': ' Requirements',
    'stats.reqValue': '0 Requirements',

    'feat.f1.title': 'Always Offline',
    'feat.f1.desc': 'The game launches directly in local offline mode. No internet required to play or create worlds.',
    'feat.f2.title': 'Global Player ID',
    'feat.f2.desc': 'Your permanent UUID identifies you across servers, future cloud saves, and multiplayer features.',
    'feat.f3.title': 'In-Game Linking',
    'feat.f3.desc': 'Link your online account directly from the Profile screen in PocketMC in 2 clicks without losing progress.',

    'how.badge': 'Step by step',
    'how.title': 'How to link your account to the game?',
    'how.subtitle': 'It is a fast 3-step process.',
    'how.s1.title': 'Create your account here',
    'how.s1.desc': 'Register on this portal choosing your unique @username and a secure password.',
    'how.s2.title': 'Launch PocketMC',
    'how.s2.desc': 'On the main menu go to Profile and click on Link PocketMC Account.',
    'how.s3.title': 'Ready to play!',
    'how.s3.desc': 'Enter your email and password. Your profile will instantly switch to Online status.',

    'footer.builtWith': 'Powered by',
    'footer.disclaimer': 'PocketMC is an open-source project. Not affiliated with Mojang or Microsoft.',

    'login.title': 'Welcome Back',
    'login.subtitle': 'Sign in to your PocketMC account',
    'login.email': 'Email address',
    'login.emailPlaceholder': 'you@example.com',
    'login.password': 'Password',
    'login.forgot': 'Forgot password?',
    'login.btn': 'Sign In',
    'login.signingIn': 'Signing in...',
    'login.noAccount': "Don't have an account?",
    'login.registerLink': 'Sign up here',
    'login.errFill': 'Please fill in all fields.',
    'login.errAuth': 'Invalid email or password.',
    'login.toastTitle': 'Welcome!',
    'login.toastMsg': 'Signed in successfully',

    'reg.title': 'Create Account',
    'reg.subtitle': 'Your official PocketMC global identity',
    'reg.username': 'Username (@handle)',
    'reg.usernamePlaceholder': 'e.g. Steve_99 (3-16 chars)',
    'reg.displayName': 'Display Name (Optional)',
    'reg.displayNamePlaceholder': 'e.g. Steve',
    'reg.email': 'Email address',
    'reg.emailPlaceholder': 'you@example.com',
    'reg.password': 'Password (min 6 characters)',
    'reg.confirmPassword': 'Confirm password',
    'reg.btn': 'Create Account',
    'reg.creating': 'Creating account...',
    'reg.hasAccount': 'Already have an account?',
    'reg.signInLink': 'Sign In',
    'reg.errUserLength': 'Username must be between 3 and 16 characters.',
    'reg.errUserFormat': 'Username can only contain letters, numbers, and underscores.',
    'reg.errPassLength': 'Password must be at least 6 characters long.',
    'reg.errPassMatch': 'Passwords do not match.',
    'reg.toastTitle': 'Account Created!',
    'reg.toastMsg': 'Welcome to PocketMC Accounts',

    'prof.online': '● Online',
    'prof.editBtn': '✏️ Edit Profile',
    'prof.username': 'Username',
    'prof.displayName': 'Display Name',
    'prof.uuid': 'PocketMC Player ID (Permanent UUID)',
    'prof.copyBtn': '📋 Copy ID',
    'prof.memberSince': 'Member Since',
    'prof.email': 'Account Email',
    'prof.signOut': 'Sign Out',
    'prof.toastCopyTitle': 'Copied!',
    'prof.toastCopyMsg': 'Player ID copied to clipboard',

    'edit.title': 'Edit Profile',
    'edit.subtitle': 'Update your visible player information',
    'edit.username': 'Username (@handle)',
    'edit.displayName': 'Display Name',
    'edit.displayNamePlaceholder': 'In-game display name',
    'edit.cancel': 'Cancel',
    'edit.save': 'Save Changes',
    'edit.saving': 'Saving...',
    'edit.success': 'Profile updated successfully!',
    'edit.toastTitle': 'Updated',
    'edit.toastMsg': 'Changes saved successfully',

    'forgot.title': 'Reset Password',
    'forgot.subtitle': 'Enter your email to receive recovery instructions',
    'forgot.email': 'Email address',
    'forgot.emailPlaceholder': 'you@example.com',
    'forgot.btn': 'Send Recovery Link',
    'forgot.sending': 'Sending link...',
    'forgot.success': 'Recovery link sent! Please check your inbox.',
    'forgot.toastTitle': 'Email Sent',
    'forgot.toastMsg': 'Instructions sent successfully',
    'forgot.backLogin': '← Back to Sign In'
  }
};

export function getLanguage() {
  const saved = localStorage.getItem('pmc_lang');
  if (saved && (saved === 'es' || saved === 'en')) return saved;
  const browserLang = navigator.language || navigator.userLanguage || '';
  return browserLang.toLowerCase().startsWith('es') ? 'es' : 'en';
}

export function setLanguage(lang) {
  if (lang !== 'es' && lang !== 'en') return;
  localStorage.setItem('pmc_lang', lang);
  applyTranslations();
  updateDropdownUI();
}

export function t(key, vars = {}) {
  const lang = getLanguage();
  let text = translations[lang]?.[key] || translations['es']?.[key] || key;
  Object.keys(vars).forEach(varKey => {
    text = text.replace(new RegExp('\\{' + varKey + '\\}', 'g'), vars[varKey]);
  });
  return text;
}

export function applyTranslations() {
  document.querySelectorAll('[data-i18n]').forEach(el => {
    const key = el.getAttribute('data-i18n');
    if (key) el.textContent = t(key);
  });

  document.querySelectorAll('[data-i18n-html]').forEach(el => {
    const key = el.getAttribute('data-i18n-html');
    if (key) el.innerHTML = t(key);
  });

  document.querySelectorAll('[data-i18n-placeholder]').forEach(el => {
    const key = el.getAttribute('data-i18n-placeholder');
    if (key) el.placeholder = t(key);
  });

  document.querySelectorAll('[data-i18n-suffix]').forEach(el => {
    const key = el.getAttribute('data-i18n-suffix');
    if (key) {
      const suffix = t(key);
      el.setAttribute('data-vela-suffix', suffix);
      const target = el.getAttribute('data-vela-target') || '0';
      el.textContent = target + suffix;
    }
  });

  document.documentElement.lang = getLanguage();
}

export function updateDropdownUI() {
  const currentLang = getLanguage();
  const label = document.getElementById('current-lang-label');
  if (label) {
    label.innerHTML = currentLang === 'es' 
      ? '<span style="margin-right:2px;">🇪🇸</span> Español' 
      : '<span style="margin-right:2px;">🇺🇸</span> English';
  }

  document.querySelectorAll('[data-lang-option]').forEach(item => {
    const lang = item.getAttribute('data-lang-option');
    if (lang === currentLang) {
      item.classList.add('active');
    } else {
      item.classList.remove('active');
    }
  });
}

export function initDropdownEvents() {
  const trigger = document.getElementById('btn-lang-trigger');
  const menu = document.getElementById('lang-dropdown-menu');

  if (trigger && menu) {
    trigger.onclick = (e) => {
      e.stopPropagation();
      menu.classList.toggle('open');
    };

    document.querySelectorAll('[data-lang-option]').forEach(item => {
      item.onclick = (e) => {
        e.stopPropagation();
        const selectedLang = item.getAttribute('data-lang-option');
        setLanguage(selectedLang);
        menu.classList.remove('open');
      };
    });

    document.addEventListener('click', () => {
      menu.classList.remove('open');
    });
  }
}

// Auto init on DOM load
document.addEventListener('DOMContentLoaded', () => {
  applyTranslations();
  updateDropdownUI();
  initDropdownEvents();
});
