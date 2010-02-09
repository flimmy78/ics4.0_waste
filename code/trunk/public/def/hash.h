#ifndef HASH_H
#define HASH_H

#ifndef NULL
#define NULL 0x00
#endif
/**
 * @file hash.h
 * @brief Axis2 Hash Tables
 */

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup hash hash
 * @ingroup util 
 * @{
 */

/**
 * When passing a key to hash_set or hash_get, this value can be
 * passed to indicate a string-valued key, and have hash compute the
 * length automatically.
 *
 * @remark hash will use strlen(key) for the length. The NUL terminator
 *         is not included in the hash value (why throw a constant in?).
 *         Since the hash table merely references the provided key (rather
 *         than copying it), hash_this() will return the NUL-term'd key.
 */
#define HASH_KEY_STRING     (-1)

/**
 * Abstract type for hash tables.
 */
    typedef struct hash_t hash_t;

/**
 * Abstract type for scanning hash tables.
 */
    typedef struct hash_index_t hash_index_t;

/**
 * Callback functions for calculating hash values.
 * @param key The key.
 * @param klen The length of the key, or HASH_KEY_STRING to use the string 
 *             length. If HASH_KEY_STRING then returns the actual key length.
 */
    typedef unsigned int (*hashfunc_t) (const char *key, int *klen);

/**
 * The default hash function.
 */
    unsigned int hashfunc_default (const char *key, int *klen);

/**
 * Create a hash table.
 * @param env The environment to allocate the hash table out of
 * @return The hash table just created
  */
  hash_t*  hash_make (void);

/**
 * Create a hash table with a custom hash function
 * @param env The environment to allocate the hash table out of
 * @param hash_func A custom hash function.
 * @return The hash table just created
  */
   hash_t*  hash_make_custom (hashfunc_t hash_func);

/**
 * Make a copy of a hash table
 * @param ht The hash table to clone
 * @param env The environment from which to allocate the new hash table
 * @return The hash table just created
 * @remark Makes a shallow copy
 */
  hash_t*  hash_copy (const hash_t *ht);

/**
 * Associate a value with a key in a hash table.
 * @param ht The hash table
 * @param key Pointer to the key
 * @param klen Length of the key. Can be HASH_KEY_STRING to use the string length.
 * @param val Value to associate with the key
 * @remark If the value is NULL the hash entry is deleted.
 */
  void  hash_set (hash_t *ht, const void *key
           , int klen, const void *val);

/**
 * Look up the value associated with a key in a hash table.
 * @param ht The hash table
 * @param key Pointer to the key
 * @param klen Length of the key. Can be HASH_KEY_STRING to use the string length.
 * @return Returns NULL if the key is not present.
 */
   void*  hash_get (hash_t *ht, const void *key
            , int klen);

/**
 * Start iterating over the entries in a hash table.
 * @param ht The hash table
 * @param p The environment to allocate the hash_index_t iterator. If this
 *          environment is NULL, then an internal, non-thread-safe iterator is used.
 * @remark  There is no restriction on adding or deleting hash entries during
 * an iteration (although the results may be unpredictable unless all you do
 * is delete the current entry) and multiple iterations can be in
 * progress at the same time.

 * @example
 */
/**
 * <PRE>
 * 
 * int sum_values(const env_t *env, hash_t *ht)
 * {
 *     hash_index_t *hi;
 *     void *val;
 *     int sum = 0;
 *     for (hi = hash_first(p, ht); hi; hi = hash_next(p, hi)) {
 *         hash_this(hi, NULL, NULL, &val);
 *         sum += *(int *)val;
 *     }
 *     return sum;
 * }
 * </PRE>
 */
 hash_index_t*  hash_first (hash_t *ht);

/**
 * Continue iterating over the entries in a hash table.
 * @param hi The iteration state
 * @return a pointer to the updated iteration state.  NULL if there are no more  
 *         entries.
 */
 hash_index_t*  hash_next (hash_index_t *hi);

/**
 * Get the current entry's details from the iteration state.
 * @param hi The iteration state
 * @param key Return pointer for the pointer to the key.
 * @param klen Return pointer for the key length.
 * @param val Return pointer for the associated value.
 * @remark The return pointers should point to a variable that will be set to the
 *         corresponding data, or they may be NULL if the data isn't interesting.
 */
 void  hash_this (hash_index_t *hi, const void **key
            , int *klen, void **val);

/**
 * Get the number of key/value pairs in the hash table.
 * @param ht The hash table
 * @return The number of key/value pairs in the hash table.
 */
   unsigned int  hash_count (hash_t *ht);

/**
 * Merge two hash tables into one new hash table. The values of the overlay
 * hash override the values of the base if both have the same key.  Both
 * hash tables must use the same hash function.
 * @param overlay The table to add to the initial table
 * @param p The environment to use for the new hash table
 * @param base The table that represents the initial values of the new table
 * @return A new hash table containing all of the data from the two passed in
 */
  hash_t*  hash_overlay (const hash_t *overlay, const hash_t *base);

/**
 * Merge two hash tables into one new hash table. If the same key
 * is present in both tables, call the supplied merge function to
 * produce a merged value for the key in the new table.  Both
 * hash tables must use the same hash function.
 * @param h1 The first of the tables to merge
 * @param p The environment to use for the new hash table
 * @param h2 The second of the tables to merge
 * @param merger A callback function to merge values, or NULL to
 *  make values from h1 override values from h2 (same semantics as
 *  hash_overlay())
 * @param data Client data to pass to the merger function
 * @return A new hash table containing all of the data from the two passed in
 */
  hash_t*  hash_merge (const hash_t *h1
           , const hash_t *h2
            , void *(*merger) (const void *key
            , int klen, const void *h1_val, const void *h2_val
            , const void *data), const void *data);

/**
 * Query whether the hash table provided as parameter contains the
 * key provided as parameter.
 *
 * @param ht hash table to be queried for key
 * @return return whether hash table contains key
 */
int  
hash_contains_key (
        hash_t *ht, 
        const char *key);
                           
/**
 * @param ht hash table to be freed
 * @param env The environment to use for hash table
 * @return return status code 
 *
 */
                           
int  hash_free(hash_t *ht);
                           
/**
 * Free a hash table with hash table given as void
 * @param ht hash table to be freed as a void *
 * @param env The environment to use for hash table
 * @return return status code
 */

int 
hash_free_void_arg (void *ht_void);

/**
 * Free all things in the  hash table and free hash table
 * @param ht hash table 
 * @return return status code
 */
typedef void (*free_key_func_t)(void *key);
typedef void (*free_data_func_t)(void *data);

int 
hash_free_all(hash_t *ht, free_key_func_t free_key, free_data_func_t free_data);

/** @} */

#ifdef __cplusplus
}
#endif

#endif                          /* !HASH_H */
