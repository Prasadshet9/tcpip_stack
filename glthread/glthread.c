#include "glthread.h"
#include <stdlib.h>

void glthread_init(glthread_t *glthread)
{
    glthread->left = NULL;
    glthread->right = NULL;
}

void glthread_add_next(glthread_t *curr, glthread_t *new_glthread)
{
    if(curr->right ==NULL)
    {
        new_glthread->left = curr;
        new_glthread->right = NULL;
        curr->right = new_glthread; 
        return;
    }

    new_glthread->right = curr->right;
    new_glthread->left = curr;
    curr->right->left = new_glthread;
    curr->right = new_glthread;
    return;
}

void glthread_add_before(glthread_t *curr, glthread_t *new_glthread)
{
    if(curr->left == NULL)
    {
        curr->left = new_glthread;
        new_glthread->left = NULL;
        new_glthread->right = curr;
        return; 
    }

    curr->left->right = new_glthread;
    new_glthread->left = curr->left;
    new_glthread->right = curr;
    curr->left = new_glthread;
    return;
}

void remove_glthread(glthread_t *glthread)
{
    if(glthread->left != NULL)
    {
        glthread->left->right = glthread->right;
    }
    if(glthread->right != NULL)
    {
        glthread->right->left = glthread->left;
    }

    glthread->left = NULL;
    glthread->right = NULL;
    return;
}

void delete_gltrhread_list(glthread_t *base_glthread)
{
    glthread_t *glthreadptr = NULL;
    ITERATE_GLTHREAD_BEGIN(base_glthread, glthreadptr)
    remove_glthread(glthreadptr);
    /*free(glthreadptr)*/ /*if allocated on Heap than free the memory*/
    ITERATE_GLTHREAD_END(base_glthread, glthreadptr)
    return;
}

void glthread_add_last(glthread_t *base_glthread, glthread_t *new_glthread)
{
    glthread_t *glthreadptr = NULL;
    glthread_t *prevglthreadptr = NULL;
    ITERATE_GLTHREAD_BEGIN(base_glthread, glthreadptr)
    prevglthreadptr = glthreadptr;
    ITERATE_GLTHREAD_END(base_glthread, glthreadptr)

    if(prevglthreadptr)
    {
        glthread_add_next(prevglthreadptr, new_glthread);
    }
    else
    {
        glthread_add_next(base_glthread, new_glthread);
    }
}

int get_glthread_list_count(glthread_t *base_glthread)
{
    int count = 0;
    glthread_t *glthreadptr = NULL;
    ITERATE_GLTHREAD_BEGIN(base_glthread, glthreadptr)
    count++;
    ITERATE_GLTHREAD_END(base_glthread, glthreadptr)
    return count;
}