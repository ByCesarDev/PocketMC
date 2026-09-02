import React, { useState } from 'react';
import { Link, useNavigate } from 'react-router-dom';
import { useAuth } from '../context/AuthContext';
import { Save, ArrowLeft, AlertCircle, CheckCircle2 } from 'lucide-react';

export default function EditProfile() {
  const { user, profile, updateProfile, loading } = useAuth();
  const navigate = useNavigate();

  const [displayName, setDisplayName] = useState(profile?.display_name || '');
  const [username, setUsername] = useState(profile?.username || '');
  const [error, setError] = useState('');
  const [success, setSuccess] = useState('');
  const [saving, setSaving] = useState(false);

  React.useEffect(() => {
    if (!loading && !user) {
      navigate('/login');
    }
    if (profile) {
      setDisplayName(profile.display_name || '');
      setUsername(profile.username || '');
    }
  }, [user, profile, loading, navigate]);

  const handleSubmit = async (e) => {
    e.preventDefault();
    setError('');
    setSuccess('');

    const cleanUsername = username.trim();
    if (!cleanUsername) {
      setError('Username cannot be empty.');
      return;
    }

    if (cleanUsername.length < 3 || cleanUsername.length > 16) {
      setError('Username must be between 3 and 16 characters.');
      return;
    }

    if (!/^[a-zA-Z0-9_]+$/.test(cleanUsername)) {
      setError('Username can only contain letters, numbers, and underscores.');
      return;
    }

    setSaving(true);

    try {
      await updateProfile({
        displayName: displayName.trim() || cleanUsername,
        username: cleanUsername,
      });
      setSuccess('Profile updated successfully!');
      setTimeout(() => navigate('/profile'), 1000);
    } catch (err) {
      setError(err.message || 'Failed to update profile.');
    } finally {
      setSaving(false);
    }
  };

  return (
    <div className="card">
      <div style={{ display: 'flex', alignItems: 'center', gap: '0.75rem', marginBottom: '1.5rem' }}>
        <Link to="/profile" className="btn btn-secondary" style={{ padding: '0.5rem', borderRadius: 'var(--radius-sm)' }}>
          <ArrowLeft size={18} />
        </Link>
        <div>
          <h2 style={{ fontSize: '1.35rem', fontWeight: 800 }}>Edit Profile</h2>
          <p style={{ color: 'var(--text-muted)', fontSize: '0.85rem' }}>Update your visible player details</p>
        </div>
      </div>

      {error && (
        <div className="alert alert-error">
          <AlertCircle size={18} />
          <span>{error}</span>
        </div>
      )}

      {success && (
        <div className="alert alert-success">
          <CheckCircle2 size={18} />
          <span>{success}</span>
        </div>
      )}

      <form onSubmit={handleSubmit}>
        <div className="form-group">
          <label className="form-label" htmlFor="username">Username (@handle)</label>
          <input
            id="username"
            type="text"
            className="form-input"
            value={username}
            onChange={(e) => setUsername(e.target.value)}
            required
          />
        </div>

        <div className="form-group" style={{ marginBottom: '1.5rem' }}>
          <label className="form-label" htmlFor="displayName">Display Name</label>
          <input
            id="displayName"
            type="text"
            className="form-input"
            value={displayName}
            onChange={(e) => setDisplayName(e.target.value)}
            placeholder="Display name in profile"
          />
        </div>

        <div style={{ display: 'flex', gap: '0.75rem' }}>
          <Link to="/profile" className="btn btn-secondary" style={{ flex: 1 }}>
            Cancel
          </Link>
          <button type="submit" className="btn btn-primary" style={{ flex: 1 }} disabled={saving}>
            <Save size={16} />
            <span>{saving ? 'Saving...' : 'Save Changes'}</span>
          </button>
        </div>
      </form>
    </div>
  );
}
