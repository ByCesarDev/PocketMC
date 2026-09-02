// Supabase Auth Integration with Vela JS
import { createClient } from 'https://cdn.jsdelivr.net/npm/@supabase/supabase-js@2/+esm';

const SUPABASE_URL = (typeof window !== 'undefined' && window.POCKETMC_CONFIG?.SUPABASE_URL) || 
                     localStorage.getItem('pmc_supabase_url') || 
                     'https://nzkzkwnfpnzplsqekggv.supabase.co';

const SUPABASE_ANON_KEY = (typeof window !== 'undefined' && window.POCKETMC_CONFIG?.SUPABASE_ANON_KEY) || 
                          localStorage.getItem('pmc_supabase_key') || 
                          'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Im56a3prd25mcG56cGxzcWVrZ2d2Iiwicm9sZSI6ImFub24iLCJpYXQiOjE3ODgyODk0NjgsImV4cCI6MjEwMzg2NTQ2OH0.qt-_QhOV78F_-06pbh37S_48UYNl-FZwOAErBaLRhsw';

export const supabase = createClient(SUPABASE_URL, SUPABASE_ANON_KEY);

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
    email: email.trim(),
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
