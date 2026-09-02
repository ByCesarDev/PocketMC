// Supabase Auth Integration with Vela JS
import { createClient } from 'https://cdn.jsdelivr.net/npm/@supabase/supabase-js@2/+esm';

const config = window.POCKETMC_CONFIG || {};
export const supabase = createClient(config.SUPABASE_URL, config.SUPABASE_ANON_KEY);

export async function getCurrentSession() {
  const { data: { session } } = await supabase.auth.getSession();
  return session;
}

export async function getProfile(userId) {
  if (!userId) return null;
  const { data, error } = await supabase
    .from('profiles')
    .select('*')
    .eq('id', userId)
    .maybeSingle();
  if (error) {
    console.error('Error loading profile:', error.message);
    return null;
  }
  return data;
}

export async function registerAccount({ username, email, password, displayName }) {
  // Check if username is available
  const { data: existing } = await supabase
    .from('profiles')
    .select('username')
    .ilike('username', username)
    .maybeSingle();

  if (existing) {
    throw new Error('This username is already taken. Please choose another.');
  }

  const { data, error } = await supabase.auth.signUp({
    email,
    password,
    options: {
      data: {
        username: username.trim(),
        display_name: (displayName || username).trim()
      }
    }
  });

  if (error) throw error;

  if (data?.user) {
    await supabase.from('profiles').upsert({
      id: data.user.id,
      username: username.trim(),
      display_name: (displayName || username).trim()
    });
  }

  return data;
}

export async function loginAccount({ email, password }) {
  const { data, error } = await supabase.auth.signInWithPassword({
    email,
    password
  });
  if (error) throw error;
  return data;
}

export async function logoutAccount() {
  const { error } = await supabase.auth.signOut();
  if (error) throw error;
}

export async function updateProfileDetails({ username, displayName }) {
  const { data: { user } } = await supabase.auth.getUser();
  if (!user) throw new Error('Not authenticated');

  const updates = {};
  if (displayName !== undefined) updates.display_name = displayName.trim();
  if (username !== undefined) {
    const cleanUser = username.trim();
    const { data: existing } = await supabase
      .from('profiles')
      .select('id')
      .ilike('username', cleanUser)
      .maybeSingle();

    if (existing && existing.id !== user.id) {
      throw new Error('This username is already taken.');
    }
    updates.username = cleanUser;
  }

  const { data, error } = await supabase
    .from('profiles')
    .update(updates)
    .eq('id', user.id)
    .select()
    .single();

  if (error) throw error;
  return data;
}

export async function requestPasswordReset(email) {
  const { data, error } = await supabase.auth.resetPasswordForEmail(email);
  if (error) throw error;
  return data;
}
